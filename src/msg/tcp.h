// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
// vim: ts=8 sw=2 smarttab
#ifndef CEPH_TCP_H
#define CEPH_TCP_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

using std::ostream;

class CephContext;

inline ostream& operator<<(ostream& out, const sockaddr_storage &ss)
{
  char buf[NI_MAXHOST] = { 0 };
  char serv[20] = { 0 };
  size_t hostlen;

  if (ss.ss_family == AF_INET)
    hostlen = sizeof(struct sockaddr_in);
  else if (ss.ss_family == AF_INET6)
    hostlen = sizeof(struct sockaddr_in6);
  else
    hostlen = sizeof(struct sockaddr_storage);
  getnameinfo((struct sockaddr *)&ss, hostlen, buf, sizeof(buf),
	      serv, sizeof(serv),
	      NI_NUMERICHOST | NI_NUMERICSERV);
  if (ss.ss_family == AF_INET6)
    return out << '[' << buf << "]:" << serv;
  return out //<< ss.ss_family << ":"
	     << buf << ':' << serv;
}

extern int tcp_read(CephContext *cct, int sd, char *buf, int len, int timeout=-1);
extern int tcp_read_wait(int sd, int timeout);
extern int tcp_read_nonblocking(CephContext *cct, int sd, char *buf, int len);
extern int tcp_write(CephContext *cct, int sd, const char *buf, int len);

inline bool operator==(const sockaddr_in& a, const sockaddr_in& b) {
  return strncmp((const char*)&a, (const char*)&b, sizeof(a)) == 0;
}
inline bool operator!=(const sockaddr_in& a, const sockaddr_in& b) {
  return strncmp((const char*)&a, (const char*)&b, sizeof(a)) != 0;
}


#endif
