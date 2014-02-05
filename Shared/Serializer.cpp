//**********************************************************************************************************************
#include "Serializer.h"
namespace Shared
{
		
		// Pre-allocate a dynamic buffer
		Serializer::Serializer(size_t buffer_size_in)
		{
			_cursor = 0;
			_bufferSize = buffer_size_in;
			_buffer = new char[buffer_size_in];
		}
		
		//passage par copie
		// Passing pbuffer_in  will cause a dynamic allocation strategy
		Serializer::Serializer(const char* pbuffer_in , size_t buffer_size_in)
		{
			_cursor = 0;
			_bufferSize = buffer_size_in;
			_buffer = new char[buffer_size_in];
			for (int i = 0 ; i < buffer_size_in ; ++i)
			{
				_buffer[i] = pbuffer_in[i];
			}
		}
		


		 Serializer::~Serializer()
		 {
			 delete _buffer;
		 }

		bool Serializer::isBigIndian() const
		{
			short int number = 0x1;
			char *numPtr = (char*)&number;
			return (numPtr[0] == 1);
		}

		void Serializer::resetCursor()
		{
			_cursor = 0;
		}

		template<typename Type>
		void Serializer::typeToBuffer(Type val_in)
		{
			size_t size = sizeof(Type);
			if ( size + _cursor > _bufferSize)
				return;
			char * tab = (char*) &val_in;

			if ( isBigIndian())
			{
				for (size_t i = 0 ; i < size ; ++i)
				{
					_buffer[_cursor++] = tab[i];
				}
			}
			else
			{
				for (size_t i = size-1 ; i >= 0 ; --i)
				{
					_buffer[_cursor++] =  tab[i];
				}
			}
		}

		template<typename Type>
		void Serializer::bufferToType(Type &val_out)
		{
			size_t size = sizeof(Type);
			if ( size + _cursor > _bufferSize)
				return;
			char* tab = (char*) &val_out;

			if ( isBigIndian())
			{
				for (size_t i = 0 ; i < size ; ++i)
				{
					tab[i] = _buffer[_cursor++] ;
				}
			}
			else
			{
				for (size_t i = size-1 ; i >= 0 ; --i)
				{
					tab[i] = _buffer[_cursor++] ;
				}
			}
		}


		//operators typeToBuffer:
		void Serializer::operator << (char val_in)
		{
			Serializer::typeToBuffer<char>(val_in);
		}
		void Serializer::operator << (netS8 val_in)
		{
			Serializer::typeToBuffer<netS8>(val_in);
		}
		void Serializer::operator << (netU8 val_in)
		{
			Serializer::typeToBuffer<netU8>(val_in);
		}
		void Serializer::operator << (netS16 val_in)
		{
			Serializer::typeToBuffer<netS16>(val_in);
		}
		void Serializer::operator << (netU16 val_in)
		{
			Serializer::typeToBuffer<netU16>(val_in);
		}
		void Serializer::operator << (netS32 val_in)
		{
			Serializer::typeToBuffer<netS32>(val_in);
		}
		void Serializer::operator << (netU32 val_in)
		{
			Serializer::typeToBuffer<netU32>(val_in);
		}
		void Serializer::operator << (const Serializer& val_in)
		{
			for (size_t i = 0 ; i < val_in._bufferSize ; ++i)
			{
				_buffer[_cursor++] = val_in._buffer[i];
			}
			_bufferSize += val_in._bufferSize;
		}



		//operators bufferToType:
		void Serializer::operator >> (char &val_out)
		{
			Serializer::bufferToType<char>(val_out);
		}
		void Serializer::operator >> (netS8 &val_out)
		{
			Serializer::bufferToType<netS8>(val_out);
		}
		void Serializer::operator >> (netU8 &val_out)
		{
			Serializer::bufferToType<netU8>(val_out);
		}
		void Serializer::operator >> (netS16 &val_out)
		{
			Serializer::bufferToType<netS16>(val_out);
		}
		void Serializer::operator >> (netU16 &val_out)
		{
			Serializer::bufferToType<netU16>(val_out);
		}
		void Serializer::operator >> (netS32 &val_out)
		{
			Serializer::bufferToType<netS32>(val_out);
		}
		void Serializer::operator >> (netU32 &val_out)
		{
			Serializer::bufferToType<netU32>(val_out);
		}
		void Serializer::operator >> (Serializer& val_out)
		{
			val_out << *this;
		}

} // namespace Shared
