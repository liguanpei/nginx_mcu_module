
/*
 * Copyright (C) Roman Arutyunyan
 */


#ifndef _NGX_RTMP_EXEC_H_INCLUDED_
#define _NGX_RTMP_EXEC_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_rtmp.h"


extern ngx_int_t
ngx_rtmp_exec_publish(ngx_rtmp_session_t *s, ngx_rtmp_publish_t *v);
//extern ngx_int_t ngx_rtmp_exec_init_process(ngx_cycle_t *cycle);


#endif /* _NGX_RTMP_EXEC_H_INCLUDED_ */
