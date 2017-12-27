//
// Created by pojol on 2017/2/13.
//

#ifndef GSF_EVENT_LIST_H_H
#define GSF_EVENT_LIST_H_H

#include "types.h"

// 后面用工具自动生成
//! 用于描述框架中用到的事件, 用户可以以此为模板在自己工程中建立一个event_list 用于工程中的事件描述

namespace eid
{
	enum base
	{
		app_id = 1,					//! 每个进程中application module 的id ，因为application的作用范围只在自身进程所以 id 可以是固定的。
		get_app_name,
		get_module,					//! 通过字符串获得module的id， 只能获取静态显示声明的module。
		new_dynamic_module,			//! ͨ通过已经定义的module，创建多份实例。
		delete_module,
		module_init_succ,
		module_shut_succ,
	};

	enum distributed
	{
		rpc_begin = 1001,

		node_create,				// by cfg
		node_create_succ,

		coordinat_regist,
		coordinat_unregit,
		coordinat_adjust_weight,	// args (i32 node_id, string module_name, i32 module_characteristic, i32 weight)
		coordinat_get,				// args (string module_name, i32 module_characteristic)

		login_server,
		login_select_gate,
		login_select_gate_cb,
		login_logout,

		rpc_end = 2000,
	};

	enum network
	{
		/*!
			创建一个接收器
		**/
		make_acceptor = 2001,
		make_connector,
		kick_connect,
		send,
		recv,
		//! result code
		new_connect,
		dis_connect,
		fail_connect,
	};

	enum log
	{
		//const uint32_t init = 1001;	初始化改为在自己模块中实现，regist即初始化
		print = 2101,
	};

	enum timer
	{
		/*!
			延迟若干毫秒触发
			参数: module_id, milliseconds
		**/
		delay_milliseconds = 2201,

		/*!
			延时一天触发， hour & minute 可以指定隔天的触发点
			参数: module_id, hour, minute
		**/
		delay_day,

		delay_week,

		delay_month,

		/*!
			从定时器中移除
			参数: timer_id
		**/
		remove_timer,

		/*!
			触发Timer
			参数: timer_id
		**/
		timer_arrive,
	};

	enum lua_proxy
	{
		/*!
			创建 Lua Script Module ,proxy会自动完成c++/lua的相关绑定 (userdata Args, interface : dispatch, listen, rpc)
			参数: proxy module_id, script_dir, script_name
		**/
		create = 2301,

		/*!
			重新装载 Lua Script Module, 会走标准的退出和进入流程 init, shut 。即便持有状态也可以方便的热更
			参数: module_id
		**/
		reload,

		/*!
			移除 Lua Script Module
			参数: module_id
		**/
		destroy,
	};

	enum db_proxy
	{
		redis_connect = 2401,
		redis_command,
		redis_avatar_offline,
		redis_resume,

		mysql_connect,
		mysql_update,
		mysql_query,
		mysql_execute,
	};

	enum error
	{
		err_repeated_fd = -10000,
		err_upper_limit_session,
		err_socket_new,
		err_socket_connect,
		err_event_eof,
		err_event_error,
		err_event_timeout,
		err_inet_pton,
		err_distributed_node_repeat,
	};

	enum sample
	{
		get_proc_path = 7000,
		get_cfg,
	};
}

#endif