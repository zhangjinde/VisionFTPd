/****************************************************************************************************

 ***********  ***********  **********
 *                 *       *         *               
 *                 *       *         *              
 *                 *       *         *              
 *******           *       **********                      
 *                 *       *                        
 *                 *       *                        
 *                 *       *                        
 *                 *       *                        

****************************************************************************************************/

#include "main.h"
#include "net_threader.h"
#include "net_messenger.h"
#include "vfs.h"


#ifndef FTPD_H
    #define FTPD_H


#define CRLF "\r\n"


typedef enum ftp_mode_e {
    ASCII,
    BINARY
} ftp_mode_t;


/* Tmp - might be overruled by VFS */
typedef struct file_transfer_s {
    size_t                    size;
    char *                    path;
    unsigned char             data_address_family;
    char *                    data_address;
    int                       data_port;
    struct file_transfer_s *  next;
} file_transfer_t;

typedef struct ftp_data_channel_s {
    int               data_sock;
    unsigned char *   data;
    buffer_state_t *  data_buf;

    struct sockaddr * dest_addr;
    socklen_t         dest_len;
    unsigned short    port;
} ftp_data_channel_t;

typedef struct ftp_state_s {
    int init;
    ftp_mode_t       mode;
    unsigned char * ftp_user;
    unsigned char * ftp_passwd;
    unsigned char * cwd;
    vfs_t *         vfs_cwd;

    net_msg_mailbox_handle_t * mailbox_handle;

    vfs_t *vfs_root;
} ftp_state_t;


buffer_state_t * create_buffer_state (int buffersize);
ftp_data_channel_t * create_ftp_data_channel (int data_sock, unsigned char * data);


void * startFTPCallbckThread (void * arg);

char * get_ftp_service_banner (void);
void set_ftp_service_banner (char *);

int move_bytes_commited_to_next_command (buffer_state_t * read_buffer_state);
int parse_long_host_port (unsigned char * long_host_port, file_transfer_t ** ft);
int parse_short_host_port (unsigned char * short_host_port, file_transfer_t ** ft);
int EPRT_to_host_port (unsigned char * str, char ** host_ip, unsigned short * port);
int PORT_to_host_port (unsigned char * str, char ** host_ip, unsigned short * port);

int handle_ftp_initialization (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_message_not_understood (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);

int handle_ftp_USER (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_PASS (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_SYST (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_FEAT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_NOOP (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_PWD  (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_CWD  (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_ABOR (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_QUIT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_TYPE (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_SIZE (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_LPRT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_EPRT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_PORT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_LIST (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);
int handle_ftp_STAT (ftp_state_t * ftp_state, buffer_state_t * read_buffer_state, buffer_state_t * write_buffer_state);



#endif /* FTPD_H */
