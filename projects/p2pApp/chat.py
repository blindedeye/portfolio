# Computer Networks: P2P Messaging App
# Author: Jake Peterson

import socket
import threading
import os
import time
import logging
import struct
import uuid

def broadcastPresence(host,port,uuids,userUuid):
    multiGroup=('224.0.0.1',10000)
    sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM,socket.IPPROTO_UDP)
    sock.setsockopt(socket.IPPROTO_IP,socket.IP_MULTICAST_TTL,2)
    message=f'{userUuid}:{uuids[userUuid]}:{host}:{port}'.encode()
    while True:
        sock.sendto(message,multiGroup)
        time.sleep(1)

def listenForPeers(local_port,peers,lock,seenMsgs,uuids,userUuid):
    sock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM,socket.IPPROTO_UDP)
    sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    sock.bind(('',10000))
    mreq=struct.pack("4sl",socket.inet_aton('224.0.0.1'),socket.INADDR_ANY)
    sock.setsockopt(socket.IPPROTO_IP,socket.IP_ADD_MEMBERSHIP,mreq)

    while True:
        data,addr=sock.recvfrom(1024)
        if not data:
            continue
        rcvUuid,username,peer_host,peer_port=data.decode().split(':')
        peer_addr=(peer_host,int(peer_port))
        with lock:
            uuids[rcvUuid]=username  # important: adding other users' uuids
        if peer_addr not in peers and int(peer_port) != local_port:
            try:
                conn_sock=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
                conn_sock.connect(peer_addr)
                with lock:
                    peers[peer_addr]=conn_sock
                threading.Thread(target=client,args=(conn_sock,peer_addr,peers,lock,seenMsgs,uuids,userUuid)).start()
            except socket.error as e:
                logging.debug(f"Failed to connect to peer at {peer_addr}: {e}")

def client(conn,addr,peers,lock,seenMsgs,uuids,userUuid):
    logging.debug(f"Connected by {addr}")
    recv_thread=threading.Thread(target=recvMessage,args=(conn,addr,peers,lock,seenMsgs,uuids,userUuid))
    recv_thread.start()
    try:
        while True:
            msg=input("")
            if msg.lower()=='quit':
                sendMessage(conn,"has left.",userUuid)
                os._exit(0)
            sendMessage(conn,msg,userUuid)
    except Exception as e:
        logging.debug(f"Error in client message sending loop: {e}")
    finally:
        conn.close()
        with lock:
            if addr in peers:
                del peers[addr]
        recv_thread.join()
        logging.debug(f"Connection closed with {addr}")

def sendMessage(sock,message,userUuid):
    msgId=f"{userUuid}|{int(time.time()*1000)}"
    full_message=f"{msgId}:{message}"
    try:
        sock.sendall(full_message.encode())
    except Exception as e:
        logging.debug(f"Failed to send message: {e}")

def recvMessage(sock,addr,peers,lock,seenMsgs,uuids,userUuid):
    try:
        while True:
            message=sock.recv(1024)
            if not message:
                break
            msgId,msg_content=message.decode().split(':',1)
            senderUuid=msgId.split('|',1)[0]
            if msgId not in seenMsgs:
                seenMsgs.add(msgId)
                print(f"{uuids[senderUuid]} [{senderUuid}]: {msg_content}")
                with lock:
                    for peer,peer_sock in list(peers.items()):
                        if peer_sock!=sock:
                            try:
                                peer_sock.sendall(message)
                            except socket.error:
                                with lock:
                                    peer_sock.close()
                                    del peers[peer]
                                logging.debug(f"Failed to forward message to {peer},closed socket.")
    except Exception as e:
        logging.debug(f"Error receiving message from {addr}: {type(e).__name__},{str(e)}")
    finally:
        with lock:
            if addr in peers:
                peers[addr].close()
                del peers[addr]
        logging.debug(f"Connection closed with {addr}")

def serverThread(HOST,config,peers,lock,ready,seenMsgs,uuids):
    with socket.socket(socket.AF_INET,socket.SOCK_STREAM) as sock:
        sock.bind((HOST,0))
        PORT=sock.getsockname()[1]
        sock.listen()
        logging.debug(f"Server started on {HOST}:{PORT}...")
        ready.set()
        username=input("Enter your username: ")
        userUuid=str(uuid.uuid4())
        uuids[userUuid]=username
        threading.Thread(target=broadcastPresence,args=(HOST,PORT,uuids,userUuid)).start()
        threading.Thread(target=listenForPeers,args=(PORT,peers,lock,seenMsgs,uuids,userUuid)).start()
        while True:
            conn,addr=sock.accept()
            with lock:
                if addr not in peers:
                    peers[addr]=conn
                    threading.Thread(target=client,args=(conn,addr,peers,lock,seenMsgs,uuids,userUuid)).start()
                else:
                    conn.close()

def init():
    logging.basicConfig(level=logging.DEBUG,format='%(asctime)s-%(levelname)s-%(message)s')
    HOST="127.0.0.1"
    peers={}
    lock=threading.Lock()
    seenMsgs=set()
    uuids={}
    config={}
    ready=threading.Event()
    threading.Thread(target=serverThread,args=(HOST,config,peers,lock,ready,seenMsgs,uuids)).start()

if __name__=='__main__':
    init()