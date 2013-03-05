/****************************************************************************!
*                _           _   _   _                                       *    
*               | |__  _ __ / \ | |_| |__   ___ _ __   __ _                  *  
*               | '_ \| '__/ _ \| __| '_ \ / _ \ '_ \ / _` |                 *   
*               | |_) | | / ___ \ |_| | | |  __/ | | | (_| |                 *    
*               |_.__/|_|/_/   \_\__|_| |_|\___|_| |_|\__,_|                 *    
*                                                                            *
*                                                                            *
* \file src/char/inter.h                                                     *
* Descri��o Prim�ria.                                                        *
* Descri��o mais elaborada sobre o arquivo.                                  *
* \author brAthena, Athena, eAthena                                          *
* \date ?                                                                    *
* \todo ?                                                                    *  
*****************************************************************************/ 

#ifndef _INTER_SQL_H_
#define _INTER_SQL_H_

struct accreg;
#include "../common/sql.h"

int inter_init_sql(const char* file);
void inter_final(void);
int inter_parse_frommap(int fd);
int inter_mapif_init(int fd);
int mapif_send_gmaccounts(void);
int mapif_disconnectplayer(int fd, int account_id, int char_id, int reason);

int inter_log(char* fmt,...);

#define inter_cfgName "conf/inter_brathena.conf"

extern unsigned int party_share_level;
extern unsigned int party_family_share_level;

extern Sql* sql_handle;
extern Sql* lsql_handle;

extern char main_chat_nick[16];
extern char tmp_db_name[32];

int inter_accreg_tosql(int account_id, int char_id, struct accreg* reg, int type);

uint64 inter_chk_lastuid(int8 flag, uint64 value);
#ifdef NSI_UNIQUE_ID
	#define updateLastUid(val_) inter_chk_lastuid(1, val_)
	#define dbUpdateUid(handler_)\
	{ \
		uint64 unique_id_ = inter_chk_lastuid(0, 0); \
		if(unique_id_ && SQL_ERROR == Sql_Query(handler_, "UPDATE `interreg` SET `value`='%"PRIu64"' WHERE `varname`='unique_id'", unique_id_)) \
				Sql_ShowDebug(handler_);\
	}
#else
	#define dbUpdateUid(handler_)
	#define updateLastUid(val_)
#endif
#endif /* _INTER_SQL_H_ */
