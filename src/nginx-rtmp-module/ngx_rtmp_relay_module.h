
/*
 * Copyright (C) Roman Arutyunyan
 */


#ifndef _NGX_RTMP_RELAY_H_INCLUDED_
#define _NGX_RTMP_RELAY_H_INCLUDED_


#include <ngx_config.h>
#include <ngx_core.h>
#include "ngx_rtmp.h"


typedef struct {
    ngx_url_t                       url;
    ngx_str_t                       app;
    ngx_str_t                       name;
    ngx_str_t                       tc_url;
    ngx_str_t                       page_url;
    ngx_str_t                       swf_url;
    ngx_str_t                       flash_ver;
    ngx_str_t                       play_path;
    ngx_int_t                       live;
    ngx_int_t                       start;
    ngx_int_t                       stop;
	ngx_str_t                       push_method;

    void                           *tag;     /* usually module reference */
    void                           *data;    /* module-specific data */
    ngx_uint_t                      counter; /* mutable connection counter */
} ngx_rtmp_relay_target_t;


typedef struct ngx_rtmp_relay_ctx_s ngx_rtmp_relay_ctx_t;

typedef struct {
    ngx_array_t                 pulls;         /* ngx_rtmp_relay_target_t * */
    ngx_array_t                 pushes;        /* ngx_rtmp_relay_target_t * */
    ngx_array_t                 static_pulls;  /* ngx_rtmp_relay_target_t * */
    ngx_array_t                 static_events; /* ngx_event_t * */
    ngx_log_t                  *log;
    ngx_uint_t                  nbuckets;
    ngx_msec_t                  buflen;
    ngx_flag_t                  session_relay;
    ngx_msec_t                  push_reconnect;
    ngx_msec_t                  pull_reconnect;
    ngx_rtmp_relay_ctx_t        **ctx;
} ngx_rtmp_relay_app_conf_t;


typedef struct ngx_rtmp_relay_app_conf_t ngx_rtmp_relay_app_t;

struct ngx_rtmp_relay_ctx_s {
    ngx_str_t                       name;
    ngx_str_t                       url;
    ngx_log_t                       log;
    ngx_rtmp_session_t             *session;
    ngx_rtmp_relay_ctx_t           *publish;
    ngx_rtmp_relay_ctx_t           *play;
    ngx_rtmp_relay_ctx_t           *next;

    ngx_str_t                       app;
    ngx_str_t                       tc_url;
    ngx_str_t                       page_url;
    ngx_str_t                       swf_url;
    ngx_str_t                       flash_ver;
    ngx_str_t                       play_path;
    ngx_int_t                       live;
    ngx_int_t                       start;
    ngx_int_t                       stop;

    ngx_event_t                     push_evt;
    ngx_event_t                    *static_evt;
    void                           *tag;
    void                           *data;
};


extern ngx_module_t                 ngx_rtmp_relay_module;


ngx_int_t ngx_rtmp_relay_pull(ngx_rtmp_session_t *s, ngx_str_t *name,
                              ngx_rtmp_relay_target_t *target);
ngx_int_t ngx_rtmp_relay_push(ngx_rtmp_session_t *s, ngx_str_t *name,
                              ngx_rtmp_relay_target_t *target);

extern ngx_rtmp_relay_ctx_t * ngx_rtmp_relay_create_connection(
       ngx_rtmp_conf_ctx_t *cctx, ngx_str_t* name,
       ngx_rtmp_relay_target_t *target);

typedef struct {
    ngx_rtmp_conf_ctx_t         cctx;
    ngx_rtmp_relay_target_t    *target;
} ngx_rtmp_relay_static_t;

typedef ngx_rtmp_relay_static_t ngx_rtmp_pull_record_t;

extern ngx_rtmp_relay_app_conf_t          *pull_racf;
extern ngx_rtmp_pull_record_t             *pull_rs;
extern ngx_int_t ngx_rtmp_relay_play_local(ngx_rtmp_session_t *s);
#endif /* _NGX_RTMP_RELAY_H_INCLUDED_ */
