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
#ifndef SLS_H
#define SLS_H

/*
  SLS - Service Lookup Service.  Yes, dumb and funny!

  SLS exists to provide a client the zeromq socket name(s) of a particular
  service the client wants to use.  The client makes a service lookup request,
  the SLS server is queried and returns the location(s) of the specified service
  to the user.
  SLS also provides a dynamic interface to allow the actual services themselves
  to register and declare their services as ready.  SLS is basically a broker
  for service discovery.  Yes, this has probably been done many times before, but this
  was an opportunity for me to play with zeromq...

  SLS is split into 2 separate interfaces:
     - Client interface (sls_client.h) to allow client lookup services.
     - Service interface (sls_service.h) to allow services to register themselves.
*/

/*
    Common constants used throughout SLS.
 */
#define SLS_MAXNAMLEN   256

/* Error codes. */
#define SLS_OK          0
#define SLS_ECONN       -1
#define SLS_EINT        -2
#define SLS_ENOTFOUND   -3

/*
 * sls_service_init
 *
 * Configure the locations of the primary and secondary SLS servers.
 * Depending on the system, this may be unnecessary.  For instance, if the client
 * is C/Linux, the primary/secondary server locations can be found by reading
 * /etc/sls-resolv.conf.  Other platforms which do not have a default setting
 * should initialize SLS with server locations using this API.
 * Also, the primary and secondary server names may be switched after
 * a lookup failure/outage.  The SLS library maintains global state
 * for the 'current' primary and secondary.  If the primary should fail,
 * the secondary will become the primary.  The SLS client library maintains
 * these designations globally for the application.
 */
void sls_init ( char *primary, char *secondary );

#endif /* SLS_H */
