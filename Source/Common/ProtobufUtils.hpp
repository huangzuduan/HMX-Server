#ifndef PROTOBUFUTILS_HPP_
#define PROTOBUFUTILS_HPP_


#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>



namespace fogs
{
namespace protobuf
{

google::protobuf::Message * getMessageFromPool(const std::string & name);


template <typename T>
T * getMessageFromPool(const std::string & name)
{
	return static_cast<T *>(getMessageFromPool(name));
}

bool setProtobufValue(google::protobuf::Message * msg,
		const std::string& field, const std::string& value);



}
}




#endif /* PROTOBUFUTILS_HPP_ */
