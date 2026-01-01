CC = gcc
CFLAGS = -O3 -Wall -Wextra -Iinclude -pg
# 소스 파일 목록: src 폴더의 모든 .c 파일
SOURCES = $(wildcard src/*.c)
# 헤더 파일 목록 (의존성 체크용)
HEADERS = $(wildcard include/*.h)

# 최종 실행 파일 이름
TARGET = kyber_test

all: $(TARGET)

$(TARGET): tests/test_kyber.c $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ tests/test_kyber.c $(SOURCES)

clean:
	rm -f $(TARGET)
