#include "helloworldservice.h"
#include <QThread>
#include "helloworldworker.h"
#include "helloworkercommand.h"

HelloWorldService::HelloWorldService(QObject *parent) :
    QObject(parent),
    m_Worker(NULL)
{
}

void HelloWorldService::startService() {
    if (m_Worker != NULL) { return; }

    m_Worker = new HelloWorldWorker();

    QThread *thread = new QThread();
    m_Worker->moveToThread(thread);

    QObject::connect(thread, SIGNAL(started()), m_Worker, SLOT(process()));
    QObject::connect(m_Worker, SIGNAL(stopped()), thread, SLOT(quit()));

    QObject::connect(m_Worker, SIGNAL(stopped()), m_Worker, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    QObject::connect(m_Worker, SIGNAL(destroyed(QObject*)),
                     this, SLOT(workerDestroyed(QObject*)));

    qInfo() << "Starting worker";

    thread->start();
}

void HelloWorldService::stopService() {
    if (m_Worker != NULL) {
        qInfo() << "Stopping worker";
        m_Worker->stopWorking();
    }
}

void HelloWorldService::submitItem(Common::IBasicArtwork *item) {
    int defaultFlags = 0;
    this->submitItem(item, defaultFlags);
}

void HelloWorldService::submitItem(Common::IBasicArtwork *item, int flags) {
    if (m_Worker == NULL) { return; }

    HelloWorkerCommand *command = new HelloWorkerCommand(item, flags);
    m_Worker->submitItem(command);
}

void HelloWorldService::submitItems(const QVector<Common::IBasicArtwork *> &items) {
    if (m_Worker == NULL) { return; }

    QVector<HelloWorkerCommand*> commands;

    int itemsLength = items.length();
    commands.reserve(itemsLength);

    for (int i = 0; i < itemsLength; ++i) {
        Common::IBasicArtwork *item = items.at(i);
        HelloWorkerCommand *command = new HelloWorkerCommand(item);
        commands.append(command);
    }

    m_Worker->submitItems(commands);
}

void HelloWorldService::workerDestroyed(QObject *object) {
    Q_UNUSED(object);
    m_Worker = NULL;
}
