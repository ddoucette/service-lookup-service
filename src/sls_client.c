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
#include "sls.h"

int sls_find_service ( char *service_name, sls_service_query_t *service_location )
{
    char   *server_response = NULL;
    int     rv;

    assert(service_name);
    assert(service_location);

    rv = sls_server_request(service_name, &server_response);
    if ( rv == SLS_OK )
    {
        /*
         * The response string should contain a string formatted
         * something like this:
         * <service name>=<URL-PRIMARY>,[URL-SECONDARY]
         * or an empty string of no such service exists.
         */
        if ( strlen(server_response) == 0 )
        {
            rv = SLS_ENOTFOUND;
            goto done;
        }

        char *primary = strchr(server_response, '=');
        if ( !primary )
        {
            /*
             * The lookup string is invalid.
             */
            rv = SLS_ESYS;
            goto done;
        }
        primary++;
        strncpy(service_location->service_name, service_name, SLS_MAXNAMLEN);
        strncpy(service_location->service_location_p, primary, SLS_MAXNAMLEN);
        char *secondary = strchr(primary, ',');
        if ( secondary )
        {
            secondary++;
            strncpy(service_location->service_location_s, secondary, SLS_MAXNAMLEN);
        }
        rv = SLS_OK;
    }
done:
    if ( server_response )
        free(server_response);
    return rv;
}

int sls_browse_services ( char *service_name, sls_service_query_t *locations[], int *nr_locations )
{
}
