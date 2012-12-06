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
    char   *sls_server_name;

    sls_server_name = sls_locate_server();
    if ( !sls_server_name )
        return SLS_ECONN;

    
}

int sls_browse_services ( char *service_name, sls_service_query_t *locations[], int *nr_locations )
{
}

