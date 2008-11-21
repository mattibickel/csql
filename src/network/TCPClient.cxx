/***************************************************************************
 *   Copyright (C) 2007 by Prabakaran Thirumalai   *
 *   praba_tuty@yahoo.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <CSql.h>
#include <Network.h>
#include <Parser.h>

TCPClient::~TCPClient()
{
   if (isConnectedFlag) disconnect();
}
DbRetVal TCPClient::send(NetworkPacketType type, char *buf, int len)
{
    DbRetVal rv = OK;
    printf("NW:TCP Send\n");
    void* totalBuffer = malloc(sizeof(PacketHeader)+ len);
    PacketHeader *hdr=  new PacketHeader();
    hdr->packetType = type;
    hdr->packetLength = len;
    hdr->srcNetworkID = networkid;
    hdr->version = 1;
    memcpy(((char*)totalBuffer) + sizeof(PacketHeader) , buf, len);
    int numbytes=0;
    if ((numbytes=os::send(sockfd, hdr, sizeof(PacketHeader), 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    printf("Sent bytes %d\n", numbytes);
    if ((numbytes=os::send(sockfd, buf, len, 0)) == -1) {
        printError(ErrOS, "Unable to send the packet\n");
        return ErrOS;
    }
    printf("Sent bytes %d\n", numbytes);
    free(totalBuffer);
    return rv;
}
DbRetVal TCPClient::receive()
{
    DbRetVal rv = OK;
    printf("NW:TCP receive\n");
    fd_set fdset; 
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getNetworkResponseTimeout();
    timeout.tv_usec = 0;
    int ret = os::select(sockfd+1, &fdset, 0, 0, &timeout);
    if (ret <= 0) {
        printError(ErrPeerTimeOut,"Response timeout for peer site\n");
        return ErrPeerTimeOut;
    }
    socklen_t len = sizeof(struct sockaddr);
    int numbytes = os::recv(sockfd, respPkt, sizeof(ResponsePacket), 0);
    if (numbytes == -1)
    {
       printf("Unable to receive response from peer\n");
       return ErrOS;
    }
    return rv;
}
DbRetVal TCPClient::connect()
{
    //printf("NW:TCP connect %s %d %d\n", hostName, port, networkid);
    //TODO::send endian to the peer site
    //do not do endian conversion here. it will be done at the server side
    isConnectedFlag = false;
    struct hostent *he;
    int numbytes;
    if ((he=gethostbyname(hostName)) == NULL) { // get the host info
        printError(ErrOS,"Unable to get the peer host name\n");
        return ErrOS;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printError(ErrOS,"Unable to create socket to peer host name\n");
        return ErrOS;
    }
    srvAddr.sin_family = AF_INET; // host byte order
    srvAddr.sin_port = htons(port); // short, network byte order
    srvAddr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(&(srvAddr.sin_zero), '\0', 8); // zero the rest of the struct
    if (::connect(sockfd, (struct sockaddr*) & srvAddr, sizeof(struct sockaddr))
         == -1)
    {
        printError(ErrOS, "Unable to connect to peer site\n");
        return ErrOS;
    }
    printf("NW:TCP connecting\n");
    fd_set fdset;
    FD_ZERO(&fdset);
    FD_SET(sockfd, &fdset);
    struct timeval timeout;
    timeout.tv_sec = Conf::config.getNetworkConnectTimeout();
    timeout.tv_usec = 0;
    int ret = os::select(sockfd+1, &fdset, 0, 0, &timeout);
    if (ret <= 0) {
        printError(ErrPeerTimeOut,"Response timeout for peer site\n");
        return ErrPeerTimeOut;
    }
    socklen_t len = sizeof(struct sockaddr);
    numbytes = os::recv(sockfd, respPkt, sizeof(ResponsePacket), 0);
    if (numbytes == -1)
    {
       printf("Unable to receive response from peer\n");
       return ErrOS;
    }
    char *response = (char *) &respPkt->retVal;
    if (*response != 1) return ErrPeerResponse;
    isConnectedFlag = true;
    return OK;

}

DbRetVal TCPClient::disconnect()
{
    if (isConnectedFlag) {
        printf("NW:TCP disconnect %s %d\n", hostName, port);
            PacketHeader *hdr=  new PacketHeader();
            hdr->packetType = NW_PKT_DISCONNECT;
            hdr->packetLength = 0;
            hdr->srcNetworkID =
            hdr->version = 1;
            int numbytes=0;
            if ((numbytes=os::send(sockfd, hdr, sizeof(PacketHeader), 0))
                == -1) {
                printError(ErrOS, "Unable to send the packet\n");
            } else
                printf("Sent bytes %d\n", numbytes);
            close(sockfd);

    }
    isConnectedFlag = false;
    return OK;
}
