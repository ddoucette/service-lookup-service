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
#include "sls_service.h"

sls_service_hndl_t sls_add_service ( sls_service_t *service )
{
    char    request_string[SLS_MAXNAMLEN];
    char   *server_response = NULL;
    int     rv;

    assert(service);

    /*
     * This API creates and sends a request to the SLS server to include this
     * service as part of its service directory.
     * As part of the 'contract' between SLS and this service, this service must
     * maintain a REQ socket to allow the SLS server to periodically query the
     * status of this service.
     * Below, we create the thread to monitor this status socket and create
     * the handle structure to manage the state.
     */
    snprintf(request_string, SLS_MAXNAMLEN, "ADD %s %s", service->service_name, service->service_location);
    rv = sls_server_request(request_string, &server_response);
    if ( rv == SLS_OK )
    {
        if ( strncmp(server_response, "OK", SLS_MAXNAMLEN) != 0 )
        {}
    }
    return NULL;
}

void sls_remove_service ( sls_service_hndl_t hndl )
{
}
