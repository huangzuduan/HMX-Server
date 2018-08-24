#ifndef FOGSMESSAGEBUFFER_HPP_
#define FOGSMESSAGEBUFFER_HPP_

#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include <stdint.h>
#include <assert.h>
//#include "GLogHelper.h"
#include "FogsProtocol.hpp"
//#include "dumpHex.h"

namespace fogs
{
namespace net
{

struct FogsMessageBuffer
{
	uint8_t *buffer;
	uint32_t size;
	uint32_t offset;
	uint32_t head;
	uint32_t tail;

	uint32_t tot_received;
	uint32_t tot_offset;



	FogsMessageBuffer(uint32_t size)
		: size(size), offset(0), head(0), tail(0), tot_received(0), tot_offset(0)
	{
		buffer = new uint8_t[size];
	}

	~FogsMessageBuffer()
	{
		delete [] buffer;
	}


	void setBytesReceived(std::size_t len,boost::system::error_code& error)
	{
		if (tail + len > size)
		{
			// TODO: how to deal with it?
			//    throw a exception
			// or
			//    return a error code?
			error = boost::system::errc::make_error_code(boost::system::errc::not_enough_memory);
			//assert(0);
		}

		tot_received += len;
		tail += len;
	}


	FogsHeader * nextMessage(boost::system::error_code& error)
	{
		FogsHeader * header = NULL;
		uint32_t available = tail - offset;
		uint32_t msgLen = 0;

		if (available >= sizeof(struct FogsHeader))
		{
			header = (FogsHeader *)(buffer + offset);

			if(header->fp_type == 0x5f776774) //start with "tgw_"
			{		
				//try skip tgw header
				std::string str = std::string((char*)(buffer + offset), (int)available);
				int pos = str.find("\r\n\r\n");

				offset += (pos + 4);
				available = tail - offset;
				if(available >= sizeof(struct FogsHeader))
				{
					header = (FogsHeader *)(buffer + offset);
				}

				////////LOG(INFO) << "header msgid " << std::hex << header->fp_msg_id;					
			}
			
			msgLen = header->fp_length + sizeof(struct FogsHeader);
			if (header->fp_length > size)
			{
				// TODO : how to deal with this?
				// - close connection
				// - discard message

				//LOG4CXX_INFO(fogs::log::gFogsLogger, "total received " << std::hex << tot_received << ", total offset " << std::hex << tot_offset);
				////////LOG(INFO) << "total received " << std::hex << tot_received << ", total offset " << std::hex << tot_offset << std::endl;
				//assert(0); // simply assert now
				error = boost::system::errc::make_error_code(boost::system::errc::bad_message);
				return NULL;
			}

			if (available < msgLen)
			{
				return NULL;
			}

			/*	if (1)
				{
					std::string * dumpStr = __dumpHex(header->fp_payload, header->fp_length);
					////////LOG(INFO) << "Recv Message:\n" <<
						"Header: type " << header->fp_type <<
						", msg_id" << header->fp_msg_id <<
						", session_id" << header->fp_session_id <<
						", length" << header->fp_length << "\n" <<
						"tot_offset : " << std::hex << tot_offset << "\n" <<
						dumpStr->c_str();
					delete dumpStr;
				}*/

			tot_offset += msgLen;
			offset += msgLen;
			return header;
		}

		return header;
	}

	boost::asio::mutable_buffers_1 makeBuffer()
	{
		rewind();
		return boost::asio::buffer(buffer + tail,
				size - tail);
	}

	void rewind()
	{

		if (head == tail)
		{
			assert(offset == tail);
			// The buffer is empty
			if (head != 0)
			{
				head = tail = offset = 0;
			}
		}
		else
		{
			if (offset != tail)
			{
				// first time rewind
				assert (tail > offset);
				if (size - tail <= 128)
				{
					memmove(buffer, buffer + offset, tail - offset);
					head = 0;
					tail = tail - offset;
					offset = head;
				}
				else
				{
					head = offset;
				}
			}
			else
			{
				/*
				 * offset == tail, not bytes left in the buffer,
				 * reset all cursors to 0
				 */
				head = tail = offset = 0;
			}
		}
	}


	std::size_t receiveAtLeast()
	{
		if (head == tail)
		{
			return sizeof(struct FogsHeader);
		}
		else
		{
			// TODO: calculate pending payload length to receive
			//       by FogsHeader.length
			return sizeof(struct FogsHeader);
		}
	}

};

}
}


#endif /* FOGSMESSAGEBUFFER_HPP_ */
