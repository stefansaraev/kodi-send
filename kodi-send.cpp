/*
 *      Copyright (C) 2008-2015 Team Kodi
 *      http://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <sys/socket.h>
#include <unistd.h>
#include "xbmcclient.h"

void showhelp(char *s)
{
  printf("Usage: %s  -a action [-h host] [-p port]\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  int opt;
  const char *action = NULL;
  const char *host = NULL;
  int port = 0;

  if(argc == 1)
    showhelp(argv[0]);

  while((opt = getopt(argc, argv, "a:h:p:")) != -1)
  {
    switch(opt)
    {
      case 'a':
        action = optarg;
        break;
      case 'h':
        host = optarg;
        break;
      case 'p':
        port = atoi(optarg);
        break;
      default:
        showhelp(argv[0]);
    }
  }

  if (!action)
    showhelp(argv[0]);

  if (!host)
    host = "127.0.0.1";

  if (!port)
    port = 9777;

  CAddress my_addr(host, port); // default => localhost on 9777

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0)
  {
    printf("Error creating socket\n");
    return -1;
  }

  printf("Sending action: \"%s\" to %s:%d\n", action, host, port);
  my_addr.Bind(sockfd);
  CPacketACTION packet(action, ACTION_BUTTON);
  packet.Send(sockfd, my_addr);
}
