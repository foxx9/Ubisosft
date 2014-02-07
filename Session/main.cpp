//**********************************************************************************************************************
#include <iostream>
#include "SessionService.h"
#include "Serializable.h"
#include "Serializer.h"
#include "NetPeer.h"


using namespace std;

int main(void)
{
	WSADATA data;
	WSAStartup(MAKEWORD(2,2),&data);
	/*
	class Bob : Shared::Serializable
	{

	public :
		int number;
		char letter;
		Bob(int n, char l)
		{
			number = n;
			letter = l;
		}

		bool Serialize(Shared::Serializer& serializer)
		{
			serializer << number;
			serializer << letter;
			return true;
		}

		bool Unserialize(Shared::Serializer& serializer)
		{
			serializer >> number;
			serializer >> letter;
			return true;
		}

	};

	cout << "size of object : " << sizeof(Bob) << endl;
	size_t val(sizeof(Bob)); 

	//init le serializer
	Shared::Serializer ser(val);

	//object a serialiser
	Bob bob(5,'b');
	cout << "object a serialiser " << endl;
	cout << "number : " << bob.number << endl;
	cout << "letter : " << bob.letter << endl;
	//serialise
	bob.Serialize(ser);

	//cursor a zero pour deserialiser
	ser.resetCursor();
	
	//objet qui va prendre les données désérialisées
	Bob receiverBob(0,'0');
	receiverBob.Unserialize(ser);

	//affiche le résultat
	cout << "object désérialisé " << endl;
	cout << "number : " << receiverBob.number << endl;
	cout << "letter : " << receiverBob.letter << endl;


	//test concaténation de serializer:
	Shared::Serializer s1(sizeof(int));
	s1 << (int) 5;

	Shared::Serializer s2(sizeof(char));
	s2 << 'o';

	Shared::Serializer s3(sizeof(char) + sizeof(int) );
	s3 << s1;
	s3 << s2;
	//meme effet : 
	// s1 >> s3;
	// s2 >> s3;

	s3.resetCursor();
	int resInt;
	char charInt;
	s3 >> resInt;
	s3 >> charInt;

	cout << "s3 (s1 << s2 ) : " << resInt << " " << charInt << endl;


	
	cout << "ce pc est BIG ENDIAN : " <<(ser.isBigIndian() ? "yep" : "nope" ) << endl;
	char * ip = "www.google.com";
	short port = 8080;
	Shared::NetPeer dkl(ip,port);

	*/

	Shared::NetPeer broker("127.0.0.1", 9042);
	
	Shared::NetworkManager netManager(broker, 9043);
	Shared::NetPeer myself("127.0.0.1", 9043);
	
	Shared::Msg msg_in;
	Shared::Msg msg_out;

	char * buffer = msg_in.GetBuffer();
	buffer[0] = 'a';
	buffer[1] = 'b';
	buffer[2] = 'c';
	msg_in.SetBufferSize(3);

	/*
	Shared::Serializer ser_in(msg_in.GetBuffer(), msg_in.GetBufferSize());
	Shared::Serializer ser_out(msg_out.GetBuffer(), msg_out.GetBufferSize());
	*/
	netManager.Init();
	netManager.Send(myself, msg_in);
	netManager.Refresh();
	netManager.Term();

	system("PAUSE");
	return 0;
}