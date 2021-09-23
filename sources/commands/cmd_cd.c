//
// Created by Antoine LANGLOIS on 22/09/2021.
//

#include "commands.h"

/* cd with only a relative or absolute path
 * - cd shall change the working directory of the current shell execution environment
 * if relative we can go in the desired directory by typing the path from the actual directory
 * if absolute we can go in the desired directory by typing the path from the root.
 * If, during the execution of the above steps, the 'PWD' environment variable is set, the 'OLDPWD' environment
 * variable shall also be set to the value of the old working directory (that is the current working directory
 * immediately prior to the call to 'cd').
 */

/* external functions that we may use :
 * - int chdir(const char *path) : changes the current working directory of the calling process to the directory
 * specified in path.
 */