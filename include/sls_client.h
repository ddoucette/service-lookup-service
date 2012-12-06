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
#ifndef SLS_CLIENT_H
#define SLS_CLIENT_H

#define SLS_MAXNAMLEN   256

/* Error codes. */
#define SLS_OK          0
#define SLS_ECONN       -1
#define SLS_EINT        -2
#define SLS_ENOTFOUND   -3


typedef struct
{
    /*
     * Service name.
     * This is a simple string identifying the service which can
     * be located using the location string below.  Service names
     * are arbitrarily chosen by the service creator and must be
     * known by the caller for a direct name resolution.
     */
    char    service_name[SLS_MAXNAMLEN];

    /*
     * Service location, primary, secondary.
     * Location of the primary server for the service named above.
     * Server locations are simply zeromq socket names.
     * Both the primary and secondary locations may be empty strings, the
     * caller should check to see if there is actually a server name
     * present.
     */
    char    service_location_p[SLS_MAXNAMLEN];
    char    service_location_s[SLS_MAXNAMLEN];

} sls_service_query_t;

/*
 * sls_find_service
 *
 * This is the primary client API to find the location(s) of known services.
 * If successful, this API will return an sls_service_query_t structure containing
 * the primary and secondary service locations (if present).
 * This API will return:
 *      : 0 (SLS_OK) on success
 *      : SLS_ECONN if it cannot connect to the SLS server(s)
 *      : SLS_EINT if the thread/process was interrupted during the lookup (signal caught).
 *      : SLS_ENOTFOUND if it cannot find the specified service name
 */
int sls_find_service ( char *service_name, sls_service_query_t *service_location );

/*
 * sls_browse_services
 *
 * Returns an array of all serices present, if the caller is curious about
 * all services offered throughout this service cluster.
 *
 * The caller must allocate the array of sls_service_query_t structures and pass
 * in the length of this allocated array.
 * On return, the number of populated array entries will be set.
 * This API will return:
 *      : 0 (SLS_OK) on success.  This doesnt necessarily mean it found any services!
 *      : SLS_ECONN if it cannot connect to the SLS server(s)
 *      : SLS_EINT if the thread/process was interrupted during the lookup (signal caught).
 */
int sls_browse_services ( char *service_name, sls_service_query_t *locations[], int *nr_locations );

#endif /* SLS_CLIENT_H */
