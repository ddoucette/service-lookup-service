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
#ifndef SLS_SERVICE_H
#define SLS_SERVICE_H

#include "sls.h"

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
     * Service location.
     * Location (zeromq-type URL name) of the service.
     * I.e. tcp://192.168.55.112:5556
     */
    char    service_location[SLS_MAXNAMLEN];

} sls_service_t;

typedef void* sls_service_hndl_t;

/*
 * sls_add_service
 *
 * This is the primary service API.  Services use this API to announce the availability
 * of their particular service.
 * If there are multiple servers registering this service, the first registering will
 * be the primary, second is the secondary, and the rest will be kept and used if the
 * primary and secondary fail.
 *
 * This API will return an sls_service_hndl_t on success, NULL on failure.
 */
sls_service_hndl_t sls_add_service ( sls_service_t *service );
void sls_remove_service ( sls_service_hndl_t hndl );

#endif /* SLS_SERVICE_H */
