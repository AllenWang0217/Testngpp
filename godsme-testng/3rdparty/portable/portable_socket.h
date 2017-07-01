/*
 *  FILE: 
 *	portable_socket.h
 *
 *  DESCRIPTION:
 *  	Opaque set of functions for (non-)blocking sockets using
 *      encryption or plaintext, with full support for systems such as Win32.  
 *      Also included are simple replacements for many Unix functions dealing with sockets.
 *
 *  FUNCTIONS:
 *      sock_nonblock() - Set socket fd to non-blocking mode. (BSD sockets only)
 *      sock_block()    - Set socket fd to blocking mode. (BSD sockets only)
 *      socketpair()    - Very simple rewrite of socketpair on Win32 for 
 *                        AF_LOCAL/SOCK_STREAM connection, with no options.
 *                        Call psocket_init() if problems with binary data occur.
 *      mysendfile()     - Linux sendfile() replacement; Is User-Space...
 *      psocket_init()  - SIGPIPE ignore for *n*x, and winsock/_fmode stuff on Windows.
 *                        Also includes OpenSSL init functions.
 *                        Please Note: this function on windows changes all pipes to binary.
 *                        If binary data becomes corrupted via socketpair, it is because the
 *                        pipes are no longer binary...
 *                        Run at the beginning of your program.
 *  	readline_r()    - Reentrant readline function with support for CRLF, 
 *                        or just CR.
 *  	fullsend()      - Write data without worrying about all of it being written.  
 *                        Useful for sockets.
 * 
 *
 * Copyright (c) 2004-2006 Karlan Thomas Mitchell<karlanmitchell@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *         This product includes software developed by
           Karlan Thomas Mitchell<karlanmitchell@comcast.net>
 * 4. Neither Karlan Thomas Mitchell nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY KARLAN THOMAS MITCHELL AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/


/*NOTE:  A Full Example is at the bottom of this document*/


/*
 * Set socket() fd to non-blocking*
 * int sock_nonblock(int sock)
 *
 * Set socket() fd to blocking
 * int sock_block(int sock)
 *
 * socketpair() for Microsoft Windows, remember to run psocket_init()
 * int socketpair(int domain, int type, int protocol, int sv[2])
 *
 * Simple Linux sendfile replacement
 * off_t mysendfile(int out_fd, FILE * in_fd, off_t *offset, off_t count)
 *
 * Called once just after main() in your program.
 * int psocket_init()
 *
 * ssize_t BIO_fullsend(BIO * bio, char * buffer, ssize_t bufferlen)
 *
 * ssize_t BIO_readline_r(BIO * bio, char * buffer, ssize_t bufferlen)
 *
 * ssize_t BIO_readline_r_timeout(BIO * bio, char * buffer, ssize_t bufferlen, struct st_timeval * time_data)
 *
 * ssize_t freadline_r(FILE * fd, char * buffer, ssize_t bufferlen)
 *
 * ssize_t readline_r(int fd, char * buffer, ssize_t bufferlen, int read_socket)
 *
 * To be used with non-blocking sockets...
 *
 * ssize_t readline_r_timeout(int fd, char * buffer, ssize_t bufferlen, int read_socket, struct st_timeval * time_data)
 *
 * WARNING: THIS FUNCTION SENDS UP TO *(buffer+buflen), zero stops nothing!
 * NOTE: The reason for above: the ability to send binary data
 * ssize_t core_fullsend(void * fd, char * buffer, ssize_t bufferlen, int socket_type)
 *
 * WARNING: If the buffer is too small, data is read up to newline [sequence],
 *            and data after the size of the buffer is discarded
 * NOTE: supports \0x0D\0x0A or \0x0A, not just \0x0D
 * NOTE: return of zero is empty line *
 * ssize_t core_readline_r_timeout(void * fd, char * buffer, ssize_t bufferlen, int socket_type, struct st_timeval * time_data)
 *
 * ssize_t core_read_timeout(void * fd, char * buffer, ssize_t bufferlen, int socket_type, struct st_timeval * time_data)
 *
 * WARNING: THIS FUNCTION SENDS UP TO *(buffer+buflen), zero stops nothing!
  NOTE: The reason for above: the ability to send binary data*
 * ssize_t fullsend(int socketd, char * buffer, ssize_t bufferlen)
 *
 * ssize_t psocket_setnonblock(struct st_psocket * psocket_data)
 * ssize_t psocket_setblock(struct st_psocket * psocket_data)
 * ssize_t psocket_setnonblock_server(struct st_psocket * psocket_data)
 * ssize_t psocket_setblock_server(struct st_psocket * psocket_data)
 * ssize_t psocket_read_timeout(struct st_psocket * psocket_data, char * buffer, size_t bufferlen, struct st_timeval * time_data)
 * ssize_t psocket_write_timeout(struct st_psocket * psocket_data, char * buffer, size_t bufferlen, struct st_timeval * time_data)
 * ssize_t psocket_readline_r_timeout(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen, struct st_timeval * time_data)
 * ssize_t psocket_read(struct st_psocket * psocket_data, char * buffer, size_t bufferlen)
 * ssize_t psocket_write(struct st_psocket * psocket_data, char * buffer, size_t bufferlen)
 * ssize_t psocket_readline_r(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen)
 * ssize_t psocket_fullsend(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen)
 * char * psocket_get_client_ip(struct st_psocket * psocket_data)
 * int psocket_getfd(struct st_psocket * psocket_data)
 * int psocket_bind(struct st_psocket * psocket_data, char * address, int short unsigned port)
 * int psocket_set_bsd(struct st_psocket * psocket_data)
 * int psocket_set_openssl(struct st_psocket * psocket_data, char * pem)
 * int psocket_copy(struct st_psocket * new_psocket, struct st_psocket * old_psocket)
 * int psocket_accept(struct st_psocket * psocket_data)
 * 
 * For connecting to a remote host, *eventually* host will support DNS names.
 * int psocket_connect(struct st_psocket * psocket_data, char * host, int unsigned short port)
 *
 * int psocket_starttls(struct st_psocket * psocket_data)
 * void psocket_shutdown(struct st_psocket * psocket_data)
 * void psocket_close_server(struct st_psocket * psocket_data)
 * void psocket_close_client(struct st_psocket * psocket_data)
 */








#ifndef _PORTABLE_SOCKET_H__
#define _PORTABLE_SOCKET_H__


#ifdef WIN32
 #ifndef __WIN32__
    #define __WIN32__
 #endif
#endif


#ifdef __WIN32__
       #ifdef __CYGWIN__
          #include <sys/types.h>
          #include <sys/socket.h>
          #include <netinet/in.h>
          #include <arpa/inet.h>
       #else
         /*Any compiler except Cygwin*/
         
          #define socklen_t int
          #include <winsock.h>
          #include <io.h>
          #include <fcntl.h>  
          
         #define INVAL_SOCK INVALID_SOCKET
         #define get_errno WSAGetLastError()

       #endif
#else
     #include <fcntl.h>
     #include <sys/ioctl.h>
     #include <sys/types.h>
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <arpa/inet.h>
     #include <netdb.h>
     #include <unistd.h>

     
     #define get_errno errno
     #define closesocket close 
     #define INVAL_SOCK -1 
     #define LPSOCKADDR  struct sockaddr *
     #define SOCKADDR_IN struct sockaddr_in
#endif

 
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

typedef size_t ssize_t;

#ifdef USE_OPENSSL
       #include <openssl/bio.h>
       #include <openssl/ssl.h>
       #include <openssl/err.h>
#endif


/*I just use closesocket on Win32 and Unix with this.
  BTW: its from windows, I know you hate that, don't u!*/
#ifndef closesocket
	#define closesocket close
#endif




/*Not included on Win32, usually. for socketpair clone*/
#ifndef AF_LOCAL
	#define AF_LOCAL AF_UNIX
#endif

/*Win32 to Unix...*/
#ifndef EWOULDBLOCK
#define EWOULDBLOCK WSAEWOULDBLOCK
#endif

/*IO is Input/Ouput method*/
#define IO_BSD     0
#define IO_OPENSSL 1

/*P is Protocol*/
#define P_TCP     0
#define P_UDP     1
#define P_TCPUDP  2



/*Passed to the core_* functions */
#define MODE_READ  0
#define MODE_WRITE 0
#define MODE_FILE  1
#define MODE_RECV  2
#define MODE_SEND  2
#define MODE_BIO   3
#define MODE_ND_FILE 4



/*Trying to milk more memory
  NOTE: This shouldn't be changed and it 
        has to do with set_openssl and get_client_ip, FYI*/
#ifdef USE_OPENSSL
   #define io_datatype struct
#else
   #define io_datatype union
#endif


struct st_psocket_bsd {
	/*Native IO Method: IO_BSD*/
	int                         serverfd;
	struct sockaddr_in          serveraddr;
	int                         clientfd;
	struct sockaddr_in          clientaddr;
};

struct st_psocket_openssl {
	#ifdef USE_OPENSSL
	/*OpenSSL IO Method: IO_OPENSSL*/
	SSL_METHOD * method;
	SSL_CTX    * ctx; /*OpenSSL connection*/
	SSL        * ssl; /*Used for SSL communication*/
	BIO        * bio;  /*Used by Accept*/
	BIO        * sbio;	/*Used for SSL communication*/
	#else
    	int msvc_dummy;
        #endif
};


struct st_psocket_union {
	struct st_psocket_bsd      bsd_io;
	struct st_psocket_openssl openssl_io;
};


/*Please memset zero sizeof(struct st_psocket) before use!*/
struct  st_psocket {
	/*NOTE: memset to zero with set defaults*/
	int io_method; /*Set it to IO_* define*/
	int protocol;  /*Set it to P_* define*/

	/*use psocket_set_bsd(), psocket_starttls() <-client, psocket_set_openssl() <-server*/

	/*BIG NOTE: set_openssl must be called AFTER bind/accept!*/

	struct st_psocket_union io_data;
};


struct st_timeval {
         long    tv_sec;         /* seconds */
         };


ssize_t core_fullread_timeout(void * fd, char * buffer, size_t bufferlen, size_t readlen, int socket_type, struct st_timeval * time_data);


#ifdef __WIN32__
#ifndef __CYGWIN__
int socketpair(int domain, int type, int protocol, int sv[2]);
#endif /*!CYGWIN*/
#endif /*Win32*/


#ifndef __LINUX__
off_t mysendfile(int out_fd, FILE * in_fd, off_t *offset, off_t count);
#else
#define mysendfile sendfile
#endif

#define psocket_init psocket_environment_init

void psocket_zero(struct st_psocket * socket_data);
int psocket_init();


/*Readline functions*/
#ifdef USE_OPENSSL
ssize_t BIO_readline_r(BIO * bio, char * buffer, ssize_t bufferlen);
#endif
ssize_t freadline_r(FILE * fd, char * buffer, ssize_t bufferlen);
ssize_t readline_r(int fd, char * buffer, ssize_t bufferlen, int read_socket);
ssize_t core_readline_r_timeout(void * fd, char * buffer, ssize_t bufferlen, int socket_type, struct st_timeval * time_data);


/*fullsend functions, thanks beej*/
#ifdef USE_OPENSSL
ssize_t BIO_fullsend(BIO *  bio, char * buffer, ssize_t bufferlen);
#endif
ssize_t core_fullsend(void * fd, char * buffer, ssize_t bufferlen, int socket_type);
ssize_t fullsend(int socketd, char * buffer, ssize_t bufferlen);
ssize_t psocket_fullsend(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen);

/*Block functions*/
int     sock_block    (int sock);
ssize_t psocket_setblock(struct st_psocket * psocket_data);
ssize_t psocket_setblock_server(struct st_psocket * psocket_data);

int     sock_nonblock (int sock);
ssize_t psocket_setnonblock(struct st_psocket * psocket_data);
ssize_t psocket_setnonblock_server(struct st_psocket * psocket_data);



ssize_t psocket_read_timeout(struct st_psocket * psocket_data, char * buffer, size_t bufferlen, struct st_timeval * time_data);
ssize_t psocket_write_timeout(struct st_psocket * psocket_data, char * buffer, size_t bufferlen, struct st_timeval * time_data);
ssize_t psocket_read(struct st_psocket * psocket_data, char * buffer, size_t bufferlen);
ssize_t psocket_write(struct st_psocket * psocket_data, char * buffer, size_t bufferlen);
ssize_t psocket_readline_r(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen);
ssize_t psocket_readline_r_timeout(struct st_psocket * psocket_data, char * buffer, ssize_t bufferlen, struct st_timeval * time_data);

char * psocket_get_client_ip(struct st_psocket * psocket_data);

int psocket_starttls(struct st_psocket * psocket_data);
int psocket_set_openssl(struct st_psocket * psocket_data, char * pem);

int psocket_getfd(struct st_psocket * psocket_data);
int psocket_bind(struct st_psocket * psocket_data, char * address, int short unsigned port);
int psocket_copy(struct st_psocket * new_psocket, struct st_psocket * old_psocket);
int psocket_accept(struct st_psocket * psocket_data);
int psocket_connect(struct st_psocket * psocket_data, char * host, int unsigned short port);
void psocket_shutdown(struct st_psocket * psocket_data);
void psocket_close_server(struct st_psocket * psocket_data);
void psocket_close_client(struct st_psocket * psocket_data);


#endif


/*
#include <stdio.h>
#include "portable_socket.h"


#include <stdlib.h>

#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/x509v3.h>
#ifndef OPENSSL_NO_ENGINE
#include <openssl/engine.h>
#endif




int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days, char * country, char * common_name);
int add_ext(X509 *cert, int nid, char *value);

int main( int   argc, char *argv[] )
{
    psocket_environment_init();

    char buffer[1024];

    if(argc == 1){
        struct st_psocket my_socket;
        printf("binding\n");
        psocket_bind(&my_socket, "0.0.0.0", 1025);
        printf("accepting\n");
        psocket_accept(&my_socket);
        create_server_key("incorp.pem", 512, 2, "US", "Incorp");
        psocket_set_openssl(&my_socket, "incorp.pem");
        psocket_readline_r(&my_socket, buffer, 1024);
        printf("buffer: %s\n", buffer);
    }
    else{
        struct st_psocket my_socket;
        printf("connecting\n");
        if(psocket_connect(&my_socket, "127.0.0.1", 1025) == 0){
            psocket_starttls(&my_socket);
            printf("connected\n");
            psocket_fullsend(&my_socket, "HELLO karlan\nhow\nkaarl", strlen("HELLO karlan\nhow\nkaarl"));
            }
    }
    exit(0);
    }


/* This below code has been taken from openssl-0.9.8b/demos/x509/ by
 * Karlan Mitchell and slightly modified...
 *


int create_server_key(char * filename, int bits, int days, char * country, char * common_name)
    {
    if(days <= 0)
        return -1;
    if(bits < 500)
        return -1;

    BIO *bio_err;
    X509 *x509=NULL;
    EVP_PKEY *pkey=NULL;

    CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);

    bio_err=BIO_new_fp(stderr, BIO_NOCLOSE);

    mkcert(&x509,&pkey,bits,0,days,country,common_name);

/*
   Lots of debugging stuff.
     RSA_print_fp(stdout,pkey->pkey.rsa,0);
     X509_print_fp(stdout,x509);
*

    FILE * incorp = fopen(filename, "w");
    if(incorp == NULL)
        return -1;


    PEM_write_PrivateKey(incorp,pkey,NULL,NULL,0,NULL, NULL);
    PEM_write_X509(incorp,x509);

    fclose(incorp);

    X509_free(x509);
    EVP_PKEY_free(pkey);

#ifndef OPENSSL_NO_ENGINE
    ENGINE_cleanup();
#endif
    CRYPTO_cleanup_all_ex_data();

    CRYPTO_mem_leaks(bio_err);
    BIO_free(bio_err);
    return(0);
    }

static void callback(int p, int n, void *arg)
    {
    char c='B';

    if (p == 0) c='.';
    if (p == 1) c='+';
    if (p == 2) c='*';
    if (p == 3) c='\n';
    fputc(c,stderr);
    }

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days, char * country, char * common_name)
    {
    X509 *x;
    EVP_PKEY *pk;
    RSA *rsa;
    X509_NAME *name=NULL;
    
    if ((pkeyp == NULL) || (*pkeyp == NULL))
        {
        if ((pk=EVP_PKEY_new()) == NULL)
            {
            abort(); 
            return(0);
            }
        }
    else
        pk= *pkeyp;

    if ((x509p == NULL) || (*x509p == NULL))
        {
        if ((x=X509_new()) == NULL)
            goto err;
        }
    else
        x= *x509p;

    rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
    if (!EVP_PKEY_assign_RSA(pk,rsa))
        {
        abort();
        goto err;
        }
    rsa=NULL;

    X509_set_version(x,2);
    ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
    X509_gmtime_adj(X509_get_notBefore(x),0);
    X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
    X509_set_pubkey(x,pk);

    name=X509_get_subject_name(x);

    /* This function creates and adds the entry, working out the
     * correct string type and performing checks on its length.
     * Normally we'd check the return value for errors...
     *
    X509_NAME_add_entry_by_txt(name,"C",
                MBSTRING_ASC, country, -1, -1, 0);
    X509_NAME_add_entry_by_txt(name,"CN",
                MBSTRING_ASC, common_name, -1, -1, 0);

    /* Its self signed so set the issuer name to be the same as the
      * subject.
     *
    X509_set_issuer_name(x,name);

    /* Add various extensions: standard extensions *
    add_ext(x, NID_basic_constraints, "critical,CA:TRUE");
    add_ext(x, NID_key_usage, "critical,keyCertSign,cRLSign");

    add_ext(x, NID_subject_key_identifier, "hash");

    /* Some Netscape specific extensions *
    add_ext(x, NID_netscape_cert_type, "sslCA");

    add_ext(x, NID_netscape_comment, "example comment extension");


#ifdef CUSTOM_EXT
    /* Maybe even add our own extension based on existing *
    {
        int nid;
        nid = OBJ_create("1.2.3.4", "MyAlias", "My Test Alias Extension");
        X509V3_EXT_add_alias(nid, NID_netscape_comment);
        add_ext(x, nid, "example comment alias");
    }
#endif
    
    if (!X509_sign(x,pk,EVP_md5()))
        goto err;

    *x509p=x;
    *pkeyp=pk;
    return(1);
err:
    return(0);
    }

/* Add extension using V3 code: we can set the config file as NULL
 * because we wont reference any other sections.
 *

int add_ext(X509 *cert, int nid, char *value)
    {
    X509_EXTENSION *ex;
    X509V3_CTX ctx;
    /* This sets the 'context' of the extensions. */
    /* No configuration database *
    X509V3_set_ctx_nodb(&ctx);
    /* Issuer and subject certs: both the target since it is self signed,
     * no request and no CRL
     *
    X509V3_set_ctx(&ctx, cert, cert, NULL, NULL, 0);
    ex = X509V3_EXT_conf_nid(NULL, &ctx, nid, value);
    if (!ex)
        return 0;

    X509_add_ext(cert,ex,-1);
    X509_EXTENSION_free(ex);
    return 1;
    }
    

*/
