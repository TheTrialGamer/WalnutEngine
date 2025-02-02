﻿#pragma once


namespace Paper
{
	using byte = uint8_t;
	struct Buffer
	{
		void* data;
		uint64_t size;

		Buffer()
			: data(nullptr), size(0)
		{
		}

		Buffer(const void* data, uint64_t size = 0)
			: data((void*)data), size(size)
		{
		}

		Buffer(const Buffer& other)
		{
			data = nullptr;
			Allocate(other.size);
			memcpy(data, other.data, other.size);
		}

		static Buffer Copy(const Buffer& other)
		{
			Buffer buffer;
			buffer.Allocate(other.size);
			memcpy(buffer.data, other.data, other.size);
			return buffer;
		}

		static Buffer Copy(const void* data, uint64_t size)
		{
			Buffer buffer;
			buffer.Allocate(size);
			memcpy(buffer.data, data, size);
			return buffer;
		}

		void Allocate(uint64_t size)
		{
			delete[](byte*)data;
			data = nullptr;

			if (size == 0)
				return;

			data = new byte[size];
			this->size = size;
		}

		void Release()
		{
			if (!data) return;
			delete[](byte*)data;
			data = nullptr;
			size = 0;
		}

		void Nullify() const
		{
			if (data)
				memset(data, 0, size);
		}

		template<typename T>
		T& Read(uint64_t offset = 0)
		{
			return *(T*)((byte*)data + offset);
		}

		template<typename T>
		const T& Read(uint64_t offset = 0) const
		{
			return *(T*)((byte*)data + offset);
		}

		byte* ReadBytes(uint64_t size, uint64_t offset) const
		{
			CORE_ASSERT(offset + size <= this->size, "Buffer overflow!");
			byte* buffer = new byte[size];
			memcpy(buffer, (byte*)data + offset, size);
			return buffer;
		}

		void Write(const void* data, uint64_t size, uint64_t offset = 0)
		{
			CORE_ASSERT(offset + size <= this->size, "Buffer overflow!");
			memcpy((byte*)this->data + offset, data, size);
		}

		operator bool() const
		{
			return data;
		}

		byte& operator[](int index)
		{
			return ((byte*)data)[index];
		}

		byte operator[](int index) const
		{
			return ((byte*)data)[index];
		}

		template<typename T>
		T* As() const
		{
			return (T*)data;
		}

		inline uint64_t GetSize() const { return size; }
	};

	//struct BufferSafe : public Buffer
	//{
	//	BufferSafe(BufferSafe& other)
	//		: data(other.data), size(other.size)
	//	{
	//	}
	//
	//	~BufferSafe()
	//	{
	//		Release();
	//	}
	//
	//	static BufferSafe Copy(const void* data, uint64_t size)
	//	{
	//		BufferSafe buffer;
	//		buffer.Allocate(size);
	//		memcpy(buffer.data, data, size);
	//		return buffer;
	//	}
	//};
}

