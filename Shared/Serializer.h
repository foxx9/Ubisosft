//**********************************************************************************************************************
#pragma once

namespace Shared
{
	//**********************************************************************************************************************
	class  Serializer
	{
	public:

		// Passing pbuffer_in  will cause a dynamic allocation strategy
		Serializer(const char* pbuffer_in = 0, size_t buffer_size_in = 0);
	
		// Pre-allocate a dynamic buffer
		Serializer(size_t buffer_size_in);

		virtual ~Serializer();

		// C Fundamental  types operations
		void operator << (char val_in);
		void operator << (signed char val_in);
		void operator << (unsigned char val_in);
		void operator << (const Serializer& val_in);

		void operator >> (char &val_out);
		void operator >> (signed char& val_out);
		void operator >> (Serializer& val_out);

	protected:

	};

} //namespace Shared
