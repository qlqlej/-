#include "extended_overlapped.h"

EXT_OVER::EXT_OVER()
{
	wsabuf.len = BUF_SIZE;
	wsabuf.buf = send_buf;
	over_type = OVER_TYPE::RECV;
	ZeroMemory(&over, sizeof(over));
}

EXT_OVER::EXT_OVER(unsigned char* packet)
{
	wsabuf.len = packet[0];
	wsabuf.buf = send_buf;
	ZeroMemory(&over, sizeof(over));
	over_type = OVER_TYPE::SEND;
	memcpy(send_buf, packet, packet[0]);
}

void EXT_OVER::SetWSABuf_length(ULONG length)
{
	if (length < 0) cout << "Wrong length value!\n";
	else wsabuf.len = length;
}
