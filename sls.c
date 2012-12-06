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

char   *g_sls_primary[SLS_MAXNAMLEN] = { 0 };
char   *g_sls_secondary[SLS_MAXNAMLEN] = { 0 };

void sls_init ( char *primary, char *secondary )
{
    assert(primary);

    strncpy(g_sls_primary, primary, SLS_MAXNAMLEN);
    if ( secondary )
        strncpy(g_sls_secondary, secondary, SLS_MAXNAMLEN);
}
