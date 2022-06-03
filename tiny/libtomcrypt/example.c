#include <stdio.h>
#include "tomcrypt_hash.h"
int main(){
    unsigned char tmp[20];
    hash_state md;


    {
        //simple example
        char *msg="abc";
        sha1_init(&md);
        sha1_process(&md, (unsigned char *)msg, (unsigned long)strlen(msg));
        sha1_done(&md, tmp);
        for (int i=0;i<20;i++)
            printf("%x ", tmp[i]);
        printf("\n");
    }

    {
        //Run SHA1 Tests
        static const struct {
        char *msg;
        unsigned char hash[20];
        } tests[] = {
            { "abc",
                { 0xa9, 0x99, 0x3e, 0x36, 0x47, 0x06, 0x81, 0x6a,
                0xba, 0x3e, 0x25, 0x71, 0x78, 0x50, 0xc2, 0x6c,
                0x9c, 0xd0, 0xd8, 0x9d }
            },
            { "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
            { 0x84, 0x98, 0x3E, 0x44, 0x1C, 0x3B, 0xD2, 0x6E,
                 0xBA, 0xAE, 0x4A, 0xA1, 0xF9, 0x51, 0x29, 0xE5,
                0xE5, 0x46, 0x70, 0xF1 }
            },
             { "The quick brown fox jumps over the lazy dog", //from wiki
            { 0x2f,0xd4,0xe1,0xc6,0x7a,0x2d,0x28,0xfc,0xed,0x84,0x9e,0xe1,0xbb,0x76,0xe7,0x39,0x1b,0x93,0xeb,0x12 }
            }
        };

        int i;
        unsigned char tmp[20];
        hash_state md;

        for (i = 0; i < (int)(sizeof(tests) / sizeof(tests[0]));  i++) {
            sha1_init(&md);
            sha1_process(&md, (unsigned char*)tests[i].msg, (unsigned long)strlen(tests[i].msg));
            sha1_done(&md, tmp);
            if (memcmp(tmp, tests[i].hash, 20) != 0) 
                return CRYPT_FAIL_TESTVECTOR;
            else
                printf("Test %d passed\n",i);
            
        }
    }

    {
        //POW example
        unsigned long k=0;
        char *powMsg="abcsfsrgfresgdrsgdsgdtgdtghdthdt";
        //allocate space for a long integer (10 digits) + 1 for any terminating null character necessary
        char *powStr=(char*) malloc( strlen(powMsg) + 10 + 1);
    
        while (1) {
        
            //TENHO a certeza que alocei bem memoria para sprintf
            #pragma GCC diagnostic ignored "-Wformat-overflow"
            sprintf(powStr, "%s%lu", powMsg,k);

            sha1_init(&md);
            sha1_process(&md, (unsigned char *)powStr, (unsigned long)strlen(powStr));
            sha1_done(&md, tmp);

            if ( 0==tmp[0] && 0==tmp[1] && 0==tmp[2])
            {
                printf("POW done : k = %lu\n",k);
                for (int i=0;i<20;i++)
                    printf("%x ", tmp[i]);
                printf("\n");
                break;
            }
            if (k%5000000==0)
                printf("searching %lu\n",k);
            k++;
        }
    }
}