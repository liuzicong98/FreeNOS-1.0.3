/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "Kill.h"
#include <FreeNOS/User.h>

Kill::Kill(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("End the process of the given process number");
    parser().registerPositional("PID", "End the process of the given process number");
}

Kill::~Kill()
{
}

Kill::Result Kill::exec()
{
    int pid = 0;

    // Convert input to pid
    if ((pid = atoi(arguments().get("PID"))) < 0)
    {
        ERROR("invalid pid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    API::Result result = ProcessCtl(pid, KillPID, EXIT_FAILURE);
    if (result == API::Success)
    {
         return Success;
    }
    else
    {
         errno = EIO;
         return IOError;
    }

}
