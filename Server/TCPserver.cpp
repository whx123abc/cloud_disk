﻿#include "TCPserver.h"
#include <qmetatype.h>
TCPserver::TCPserver(QObject *parent)
	: QTcpServer(parent)
{
	qRegisterMetaType<qintptr>("qintptr");
	qDebug() << "Server running";
}

TCPserver::~TCPserver()
{
}

void TCPserver::incomingConnection(qintptr socketDescriptor)
{
	QThread *tem_thread = new QThread();
    threads[socketDescriptor] = tem_thread; //用于记录线程数
	TCPsocket *socket = new TCPsocket();
	socket->moveToThread(tem_thread);
	connect(tem_thread, &QThread::finished, socket, &QObject::deleteLater);
	connect(this, &TCPserver::socket_init, socket, &TCPsocket::socket_init);
	connect(socket, &TCPsocket::string_to_server_ready, this, &TCPserver::handle_string_from_socket);
	tem_thread->start();
    emit socket_init(socketDescriptor);//在将对象移入新线程后再进行socket初始化 否则不好使
	disconnect(this, &TCPserver::socket_init, socket, &TCPsocket::socket_init);
	qDebug() << "New thread,threads now:"<<threads.count();
}



void TCPserver::handle_string_from_socket(const QString & str)
{
	QStringList list = str.split("****");
	if (list.at(0) == "disconnect") {
		qDebug() << list.at(1);
		qintptr tem = list.at(1).toLongLong();
		if (threads.contains(tem) ){
			threads.value(tem)->quit();
			threads.remove(tem);
			qDebug() <<"A thread quit,threads now:"<< threads.count();
		}
	}
	else if (list.at(0) == "debug") {
		qDebug() << "Debug from thread:" << list.at(1);
	}
	
}
