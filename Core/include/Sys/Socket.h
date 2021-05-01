#ifndef __SOCKET_H__
#define __SOCKET_H__

//#include "BaseTypes.h" in buffer.h
#include "Sys/Thread.h"
#include "Sys/Buffer.h"

struct DLL_API Net{//http://beej.us/guide/bgnet/output/html/singlepage/bgnet.html  http://tangentsoft.net/wskfaq/examples/rawping.html

	struct DLL_API ip_adr{
		sockaddr_in adr;//sockaddr_in6 
		char tmp[30];//'xxx.xxx.xxx.xxx'=12+':xxxxx'=6 =18

		ip_adr();
		ip_adr(int ip);
		void clear();

		void set_ip(int new_ip);
		void set_port(int nport);
		void set(int new_ip, int nport);
		void set(char *chars_ip4p);
		bool load(const char *fname);
		char *print();
		int part(int n);
	};


	struct DLL_API Socket{
		SOCKET S, Accepted;
		ip_adr to, from;

		bool InitUDP();
		bool InitTCP();
		bool setTTL(int ttl);
		bool setForceOpt(int opt);
		bool Close();

		int SendTo(sockaddr_in *TO, const char *data, int len);
		bool Receive(char *data, int &len);

		void ClientConnect();// sockaddr_in *TO);

		void ServerBind(int port);
		void ServerListen(int num_connections);
		void ServerAccept();
	};


	BUFFER Sbuf, Rbuf;
	Socket in, out;
	ip_adr dst;//multiple?
	Thread *in_thread, *out_thread;
	int local_ips[16];//16 max?
	int ip;//current active from local_ips[]

	Net();
	~Net();
	void init();
	void in_thread_loop();
	void out_thread_loop();
	void try_connect();
};

#endif
