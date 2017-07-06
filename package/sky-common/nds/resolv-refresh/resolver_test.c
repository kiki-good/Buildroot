#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define _PATH_RESOLV_CONF "/etc/resolv.conf"
#define _PATH_BACKUP_RESOLV_CONF "/tmp/resolv.backup.conf"
#define _PATH_BAD_RESOLV_CONF "/tmp/resolv.bad.conf"

int activate_bad_resolv_conf(void)
{
    struct stat statbuf;
    FILE *fp;
    
    fprintf(stderr, "--> %s\n", __FUNCTION__);

    /* backup good config */
    rename(_PATH_RESOLV_CONF, _PATH_BACKUP_RESOLV_CONF);
    
    /* generate bad config if needed*/
    if (stat(_PATH_BAD_RESOLV_CONF, &statbuf) < 0)
    {
        fp = fopen(_PATH_BAD_RESOLV_CONF, "w");
        fputs("nameserver", fp);
        fflush(fp);
        fclose(fp);
    }
    
    rename(_PATH_BAD_RESOLV_CONF, _PATH_RESOLV_CONF);

}

int activate_good_resolv_conf(void)
{
    fprintf(stderr, "--> %s\n", __FUNCTION__);
    
    rename(_PATH_RESOLV_CONF, _PATH_BAD_RESOLV_CONF);
    rename(_PATH_BACKUP_RESOLV_CONF,_PATH_RESOLV_CONF);
}


int gethostbyname_test(char *hostname, char * ipstring)
{
  struct hostent *he;
    struct in_addr a;
    
    he = gethostbyname(hostname);
    if (he)
    {
        #if 0
        fprintf(stderr, "name: %s\n", he->h_name);
        #endif
        #if 0
        while (*he->h_aliases)
            fprintf(stderr, "alias: %s\n", *he->h_aliases++);
        #endif
        if (*he->h_addr_list)
        {
            bcopy(*he->h_addr_list++, (char *) &a, sizeof(a));
            
            /* should really pass the size, result needed by subsequent test*/
            strncpy(ipstring,(char*)inet_ntoa(a),INET6_ADDRSTRLEN);
            fprintf(stderr, "%s: PASSED %s -> %s\n", __FUNCTION__, hostname, ipstring);
            return 0;
        }
        else
        {
            fprintf(stderr, "%s: FAILED\n", __FUNCTION__);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "%s: FAILED\n", __FUNCTION__);
        return 1;
    }
}

int gethostbyaddr_test(char *ipstr)
{
    {
       struct in_addr ip;
       struct hostent *hp;

       if (!inet_aton(ipstr, &ip))
       {   
            //fprintf(stderr, "can't parse IP address %s", ipstr);
            fprintf(stderr, "%s: EXCEPTION: can't parse IP address %s\n", __FUNCTION__, ipstr);
            return 1;
       }            

       if ((hp = gethostbyaddr((const void *)&ip, sizeof ip, AF_INET)) == NULL)
       {
           fprintf(stderr, "%s: FAILED\n", __FUNCTION__);
           return 1;
       }

       fprintf(stderr,"%s: PASSED: %s -> %s\n", __FUNCTION__, ipstr, hp->h_name);
    }
    return 0;
}

int getaddrinfo_test(char *fqdn, struct addrinfo ** result)
{
    int error;
    union {
    struct sockaddr gen;
    struct sockaddr_in in;
    struct sockaddr_in6 in6;
    } sa;
    void *p;
    
    /* resolve the domain name into a list of addresses */
    error = getaddrinfo(fqdn, NULL, NULL, result);
 
    if (0 != error)
    {   
        //fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
        fprintf(stderr, "%s: FAILED\n", __FUNCTION__);
        return 1;
    }
    
    fprintf(stderr, "%s: PASSED", __FUNCTION__);
    {
        char ipstring[INET6_ADDRSTRLEN];
        memcpy (&sa, (*result)->ai_addr, (*result)->ai_addrlen);
        
        switch ((*result)->ai_family) {
            case AF_INET: /* IPv4 */
            p = &(sa.in.sin_addr);
            break;
            
            
            case AF_INET6: /* IPv6 */
            p = &(sa.in6.sin6_addr);
            break;
            
            default:
            p = &(sa.gen.sa_data);
            break;
        }
        
        inet_ntop ((*result)->ai_family, p, ipstring,  sizeof (ipstring));
        //inet_ntop ((*result)->ai_family, &(sa.in.sin_addr), ipstring,  sizeof (ipstring));
        
        fprintf(stderr, " %s -> %s",fqdn, ipstring);
    }
    fprintf(stderr, "\n");
    return 0;
}

int getnameinfo_test(struct addrinfo * result)
{
#ifndef   NI_MAXHOST
#define   NI_MAXHOST 1025
#endif
    if(result != NULL)
    {
        char hostname[NI_MAXHOST] = "";

        if( getnameinfo(result->ai_addr, result->ai_addrlen, hostname, NI_MAXHOST, NULL, 0, NI_NAMEREQD)!= 0) 
        {   
            fprintf(stderr, "%s: FAILED\n", __FUNCTION__);
            return 1;
        }
        fprintf(stderr, "%s: PASSED", __FUNCTION__);
        if (*hostname)
            fprintf(stderr," -> %s\n", hostname);
        else
            fprintf(stderr, "\n");
    }
    else
    {   
        fprintf(stderr, "%s: EXCEPTION: wrong test function input data\n", __FUNCTION__);
        return 1;
    }  
    
    return 0;
}

int
main (int argc, char **argv)
{
    struct hostent *he;
    struct in_addr a;
    char hostname[256];
    struct addrinfo * result;
    char ipstring[INET6_ADDRSTRLEN];
    int errors = 0;
    
    fprintf(stderr, " ******** test_resolver started *********\n");
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        return 1;
    }
    
    strncpy(hostname,argv[1],256);
    
    {/*-------------------------*/
        fprintf(stderr, " ******** gethostbyname_test *********\n");
        if(gethostbyname_test(hostname, ipstring) !=0)
            errors++;
        
        activate_bad_resolv_conf();
        if(gethostbyname_test(hostname, ipstring) ==0)
            errors++;
        
        activate_good_resolv_conf();
        if (gethostbyname_test(hostname, ipstring) != 0)
        {
            // "ipstring" is needed in following test
            fprintf(stderr, " EXCEPTION, test failed\n");
            errors++;
            exit(1);
        }
    }
        
    {/*-------------------------*/
        fprintf(stderr, " ******** gethostbyaddr_test *********\n");
        if (gethostbyaddr_test(ipstring)!=0)
            errors++;
        
        activate_bad_resolv_conf();
        if (gethostbyaddr_test(ipstring)==0)
            errors++;
        
        activate_good_resolv_conf();
        if (gethostbyaddr_test(ipstring)!=0)
            errors++;
    }

    {/*-------------------------*/
        fprintf(stderr, " ******** getaddrinfo_test *********\n");
        if (getaddrinfo_test(hostname,&result)!=0)
            errors++;
        
        activate_bad_resolv_conf();
        if (getaddrinfo_test(hostname,&result)==0)
            errors++;
        
        activate_good_resolv_conf();
        if (getaddrinfo_test(hostname,&result) !=0)
        {
            // "result" is needed in following test
            fprintf(stderr, " EXCEPTION, test failed\n");
            errors++;
            exit(1);
        }
    }
    
    {/*-------------------------*/
        fprintf(stderr, " ******** getnameinfo_test *********\n");
        if (getnameinfo_test(result)!=0)
            errors++;
        
        activate_bad_resolv_conf();
        if (getnameinfo_test(result)==0)
            errors++;
        
        activate_good_resolv_conf();
        if (getnameinfo_test(result)!=0)
            errors++;
    }
    freeaddrinfo(result);
    
    fprintf(stderr, "OVERAL result: ");
    if(errors)    
        fprintf(stderr, "FAILED numerrors: %d\n", errors);
    else
        fprintf(stderr, " PASSED\n");
    return 0;
}

