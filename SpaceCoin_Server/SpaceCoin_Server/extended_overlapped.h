#include "stdafx.h"

class EXT_OVER {
private:
	WSAOVERLAPPED		over;
	WSABUF				wsabuf;
	char				send_buf[BUF_SIZE];
	OVER_TYPE			over_type;

public:
	EXT_OVER();
	EXT_OVER(unsigned char* packet);

	int target_id;

	WSAOVERLAPPED& GetWSAOverlapped() { return over; }
	WSABUF& GetWSABuf() { return wsabuf; }
	char* GetSendBuf() { return send_buf; }
	OVER_TYPE GetOverType() { return over_type;	}

	void SetWSABuf_length(ULONG length);
	void SetWSABuf_buf(char* buf) { wsabuf.buf = buf; }
	void SetOverType(OVER_TYPE type) { over_type = type; }
};