/*
    Copyright (c) 2012 Dan Doucette

    SLS is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    SLS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "czmq.h"

char       *g_sls_primary[SLS_MAXNAMLEN] = { 0 };
char       *g_sls_secondary[SLS_MAXNAMLEN] = { 0 };
zmutex_t   *g_lock = NULL;

//  --------------------------------------------------------------------------
//  Receive C string from socket. Caller must free returned string. Returns
//  NULL if the context is being terminated or the process was interrupted.

char *
zstr_recv_timeout (void *zocket, int timeout)
{
    assert (zocket);
    zmq_msg_t message;
    zmq_msg_init (&message);
    if (zmq_recvmsg (zocket, &message, timeout) < 0)
        return NULL;

    size_t size = zmq_msg_size (&message);
    char *string = (char *) malloc (size + 1);
    memcpy (string, zmq_msg_data (&message), size);
    zmq_msg_close (&message);
    string [size] = 0;
    return string;
}

void sls_init ( char *primary, char *secondary )
{
    assert(primary);
    assert(!g_lock);

    g_lock = zmutex_new();
    assert(g_lock);

    strncpy(g_sls_primary, primary, SLS_MAXNAMLEN);
    if ( secondary )
        strncpy(g_sls_secondary, secondary, SLS_MAXNAMLEN);
}

int sls_server_request ( char *request, char **response )
{
    char    server_name[SLS_MAXNAMLEN];
    int     attempt;
    int     rv = SLS_OK;
    zctx_t *ctx = zctx_new();

    assert(request);
    assert(response);

    for ( attempt = 0; attempt < 2; attempt++ )
    {
        zmutex_lock(g_lock);
        if ( attempt == 0 )
            strncpy(server_name, g_sls_primary, SLS_MAXNAMLEN);
        else
            strncpy(server_name, g_sls_secondary, SLS_MAXNAMLEN);
        zmutex_unlock(g_lock);

        /*
         * Check the server name, there may not be a secondary or
         * a primary server configured...
         */
        if ( strnlen(server_name, SLS_MAXNAMLEN) == 0 )
            break;

        void *sls_socket = zsocket_new (ctx, ZMQ_REQ);
        if ( !sls_socket )
        {
            rv = SLS_ESYS;
            break;
        }

        if ( zsocket_connect (sls_socket, server_name) != 0 )
        {
            rv = SLS_ECONN;
            continue;
        }

        zstr_send (sls_socket, request);
        *response = zstr_recv_timeout (client, SLS_TIMEOUT);
        if (!*response)
        {
            rv = SLS_ECONN;
            continue;
        }
        rv = SLS_OK;

        if ( attempt > 0 )
        {
            /*
             * We failed the lookup attempt on the primary, then
             * the secondary worked.  Switch the two servers around.
             */
            zmutex_lock(g_lock);
            /*
             * Under lock, confirm the secondary is still the server
             * we just used.  Another thread may have already 
             * swapped the two server names.
             */
            if ( strncmp(server_name, g_sls_secondary, SLS_MAXNAMLEN) == 0 )
            {
                char tmp[SLS_MAXNAMLEN];
                strncpy(tmp, g_sls_primary, SLS_MAXNAMLEN);
                strncpy(g_sls_primary, g_sls_secondary, SLS_MAXNAMLEN);
                strncpy(g_sls_secondary, tmp, SLS_MAXNAMLEN);
            }
            zmutex_unlock(g_lock);
        }
        break;
    }
    zctx_destroy(&ctx);
    return rv;
}
