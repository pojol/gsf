# GSF
[![Build Status](https://travis-ci.org/pojol/gsf.svg?branch=master)](https://travis-ci.org/pojol/gsf)
[![License](http://img.shields.io/badge/license-mit-blue.svg?style=flat-square)](https://raw.githubusercontent.com/labstack/echo/master/LICENSE)

## feature
- 组件结构，模块访问隔离
- 基于命令（接口）编程
- 有一定的内省能力（可以运行时开启资源，性能的使用报告
- 支持使用c/c++, lua编写模块 (lua模块可在运行时重载
- 支持分布式架构（可依据业务定制，建议多对数据进行分片，少同步
- 跨平台 （linux, windows

## modules
| module        |       event           |             comment                  |    test case    |
| :----      |:----:                 | :-----:                       | :-----:  |
| core          | [core](#core)   | 提供框架基础的支撑服务        | |
| network::acceptor      |      [network](#network)        |   基于libevent的接收器封装    | |
| network::connector      |      [network](#network)       |    基于libevent的连接器封装   | |
| distributed::coordinat| [distributed](#distributed)| 处理集群中的协调服务 | |
|distributed::node| [distributed](#distributed) | 处理集群中的远程分发和绑定相关服务 |
|lua_proxy| [lua_proxy](#lua) | 管理LuaModule的状态以及和c++层的交互 ||
|timer| [timer](#timer)| 定时器相关
|mysql_proxy| [mysql_proxy](#mysql_proxy)| mysql封装 |
|redis_proxy| [redis_proxy](#redis_proxy)| redis的封装目前主要作用于灾备和mysql更新优化 |
|logger| [logger](#logger)| 基于glog的日志模块 |



## build & install 
- supported compilers , gcc4.9+, vs2015+
- depend cmake2.8+ 
- build (linux
    - python 3rd/update_3rd.py
    - mkdir build
    - cd build
    - cmake ..
    - make

	
## sample
- https://github.com/pojol/gsf_sample
- [x] timer
- [x] echo
- [x] db_proxy
- [x] distributed

## core
```c++
enum base
{
	/*!
		comment: 通过字符串获得module的id， 只能获取静态显示声明的module。
		args: string module_name
		type: dispatch
		res : int32_t module_id 
	**/
	get_module,

	/*!
		comment: 运行过程中创建Module，需要通过 REGISTER_CLASS 提前进行类型定义。
		args: string module_type
		type: dispatch 
		res : int32_t module_id
	**/
	new_dynamic_module,
	
	/*!
		comment: 移除注册在App中的某个Module
		args: int32_t module_id
		type: dispatch
		res : nil
	**/
	delete_module,

	/*!
		comment: 在集群中创建一个唯一ID，需要用户通过config.machine 为App做好区分。
		args: nil
		type: dispatch
		res : int64_t uuid
	**/
	uuid,
};
```
## network
```c++
enum network
{
	/*!
		comment: 创建一个接收器
		args: int32_t module_id, string ip, int32_t port
		type: dispatch
		res : bool succ or fail, string reason
	**/
	make_acceptor = 2001,

	/*!
		comment: 创建一个连接器
		args: module_id, ip, port
		type: dispatch
		res : bool succ or fail, string reason
	**/
	make_connector,

	/*!
		comment: 踢掉某个现有的连接
		args: int32_t fd
		type: dispatch
		res : bool succ or fail, string reason
	**/
	kick_connect,

	/*!
		comment: 发送一条网络消息
		args: int32_t fd, int32_t msgid, stream block
		type: dispatch
		res : nil
	**/
	send,

	/*!
		comment: 接收到一条网络消息
		args: int32_t fd, int32_t msgid, stream block
		type: listen
		res : nil
	**/
	recv,
	
	/*!
		comment: 接收到一个新的连接（适用于 acceptor
		args: int32_t fd
		type: listen
		res : nil
	**/
	new_connect,

	/*!
		comment: 连接被断开
		args: int32_t fd
		type: listen
		res : int32_t fd, string reason
	**/
	dis_connect,
};
```
## distributed
```c++
//! 凡是gsf集群内使用rpc交互的消息都应该定义在distributed区块
enum distributed
{
	/*!
		comment: 将Node绑定到Coordinator
		args: string node_type, int32_t node_id, string root_ip, int32_t root_port, [{string module_name, int32_t module_id, int32_t module_fature} ... ]
		type: rpc
		res : stream args, int32_t progress, bool succ
	**/
	coordinat_regist,
	
	/***/
	coordinat_unregit,

	/*!
		comment: 调整Node在Coordinator中的权重
		args: int32_t node_id, string module_name, int32_t module_fature, int32_t +- weight 
		type: rpc
		res : stream args, int32_t progress, bool succ
	**/
	coordinat_adjust_weight,

	/*!
		comment: 通过ModuleName和ModuleFeature选取一个适合自己的Node
		args: string module_name, int32_t module_fature
		type: rpc
		res : stream args, int32_t progress, bool succ
	**/
	coordinat_select,

	/**!
		comment: 查询Mysql数据库， args中存放单条查询信息， 如果返回的是数组 progress 则代表当前进度 -1 代表eof
		args: moduleid, sql
		type: rpc
		res : stream args, int32_t progress, bool succ
	*/
	mysql_query,
};
```
## lua
```c++

```

## timer
```c++

```

## mysql_proxy
```c++

```

## redis_proxy
```c++

```

## logger
```c++

```
