#ifndef _GSF_VARS_HEADER_
#define _GSF_VARS_HEADER_

#include "variant.h"
#include <vector>
#include <assert.h>
#include <memory>

namespace gsf
{
	class Arg
	{
		typedef Variant<bool, uint32_t, int32_t, uint64_t, int64_t, std::string, std::function<void(std::string)>> av;
	public:
		void set_bool(const bool var)
		{
			v_ = bool(var);
		}

		void set_uint32(const uint32_t var)
		{
			v_ = uint32_t(var);
		}

		void set_int32(const int32_t var)
		{
			v_ = int32_t(var);
		}

		void set_uint64(const uint64_t var)
		{
			v_ = uint64_t(var);
		}

		void set_int64(const int64_t var)
		{
			v_ = int64_t(var);
		}

		void set_string(const std::string &var)
		{
			v_ = std::string(var);
		}

		void set_remote_callback(std::function<void(std::string)> var)
		{
			v_ = var;
		}

		av v_;
	};

	class Args
	{
	public:
		Args()
			: size_(0)
		{

		}

		void add(const bool value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_bool(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(const uint32_t value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_uint32(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(const int32_t value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_int32(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(const uint64_t value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_uint64(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(const int64_t value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_int64(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(const std::string &value)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_string(value);

			size_++;
			arg_list_.push_back(_arg);
		}

		void add(std::function<void(std::string)> func)
		{
			auto _arg = std::make_shared<Arg>();
			_arg->set_remote_callback(func);

			size_++;
			arg_list_.push_back(_arg);
		}

		const bool pop_bool(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return false;
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<bool>();
		}

		const int32_t pop_int32(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return 0;
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<int32_t>();
		}

		const uint32_t pop_uint32(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return 0;
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<uint32_t>();
		}

		const uint64_t pop_uint64(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return 0;
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<uint64_t>(); 
		}

		const uint64_t pop_int64(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return 0;
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<int64_t>(); 
		}

		const std::string & pop_string(const int index)
		{
			#ifdef _DEBUG
				assert(index >= 0 && index < size_);
			#else
				if (index < 0 || index >= size_){
					return "";
				}
			#endif

			auto var = arg_list_[index];
			return var->v_.Get<std::string>();
		}

		const std::function<void(std::string)> pop_remote_callback(const int index)
		{
#ifdef _DEBUG
			assert(index >= 0 && index < size_);
#else
			if (index < 0 || index >= size_) {
				return nullptr;
			}
#endif
			auto var = arg_list_[index];
			return var->v_.Get<std::function<void(std::string)>>();
		}

		Args & operator << (const bool value)
		{
			add(value);
			return *this;
		}

		Args & operator << (const uint32_t value)
		{
			add(value);
			return *this;
		}

		Args & operator << (const int32_t value)
		{
			add(value);
			return *this;
		}

		Args & operator << (const uint64_t value)
		{
			add(value);
			return *this;
		}

		Args & operator << (const int64_t value)
		{
			add(value);
			return *this;
		}

		Args & operator << (const std::string &value)
		{
			add(value);
			return *this;
		}

		Args & operator << (std::function<void(std::string)> value)
		{
			add(value);
			return *this;
		}

		int get_count() const
		{
			return size_;
		}

	private:
		std::vector<std::shared_ptr<Arg>> arg_list_;

		int size_;
	};

	/*
		Args args;
		args.add("hello");

		std::cout << args.pop_string(0).c_str() << std::endl;
		
		Args args;
		args << 10 << "hello";

		std::cout << args.pop_uint32(0) << args.pop_string(1).c_str() << std::endl;
	*/
}

#endif
