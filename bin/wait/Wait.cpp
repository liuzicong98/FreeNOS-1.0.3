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
#include <sys/types.h>
#include <sys/wait.h>
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("It should be able to wait for a background process.");
    parser().registerPositional("PID", "It should be able to wait for the number of background process.");
}

Wait::~Wait()
{
}

Wait::Result Wait::exec()
{
    pid_t pid = 0;
    char command[150];
    char buf[300];

    // Convert input to seconds
    if ((pid = atoi(arguments().get("PID"))) <= 0)
    {
        ERROR("invalid pid `" << arguments().get("PID") << "'");
        return InvalidArgument;
    }

    snprintf(command, sizeof(command), "ps %d", pid);
    FILE* fp=NULL;
    // Wait now
    while(1){
    	
    	fp=popen(command, "r");
    	if((fgets(buf, sizeof(buf), fp))==NULL){
    	    ERROR("failed to wait: " << strerror(errno));
            return IOError;
    	}
   	if((fgets(buf, sizeof(buf), fp)) == NULL) break;
    }
    

    // Done
    return Success;
}
