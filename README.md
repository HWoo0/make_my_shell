# Minishell
Bash의 핵심 기능을 구현한 경량 쉘 프로그램

## 프로젝트 개요
- **개발 기간**: 2024.05 ~ 2024.06  
- **사용 기술**: C, System Call (fork, execve, pipe, signal)
- **프로젝트 목적**: Bash의 명령어 처리 방식을 학습하고, 프로세스 제어와 파이프라인을 직접 구현하여 운영체제의 핵심 동작 원리에 대한 이해 습득

## 주요 기능
- 명령어 파싱 및 실행
- 내장 명령어 구현 (echo, cd, pwd, exit, env, export, unset)
- 파이프(|) 및 리다이렉션(>, <, >>) 처리
- 환경 변수 관리 및 확장
- 시그널(Ctrl+C, Ctrl+\\) 처리

## 핵심 구현 내용
- **명령어 파싱**: 공백, 인용부호, 파이프, 리다이렉션을 구분하는 토큰화
- **프로세스 실행**: fork/execve를 통한 명령어 실행 및 waitpid로 자식 프로세스 관리
- **파이프라인 처리**: pipe()와 dup2()를 활용한 다중 명령 연결
- **시그널 핸들링**: SIGINT, SIGQUIT 제어를 통한 안전한 인터럽트 처리

## 기술적 성과
- Bash 주요 기능(pipe, redirect, builtin, signal) 구현
- 파일 디스크립터 충돌 문제 해결
- 리눅스 시스템 호출 기반 프로세스 제어 구조 이해

## 실행 방법
```bash
make
./minishell
```

## 학습 내용
- 프로세스 생성 및 제어 (fork, execve, waitpid)
- 파이프라인 및 리다이렉션 (pipe, dup2)
- 시그널 처리 (SIGINT, SIGQUIT)
- 명령어 파싱 및 문자열 처리
