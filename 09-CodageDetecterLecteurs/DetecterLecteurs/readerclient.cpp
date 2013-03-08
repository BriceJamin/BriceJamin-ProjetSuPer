#include "readerclient.h"

ReaderClient::ReaderClient
    (int num, int lieu, QString ip, bool estConnecte, QObject *parent = 0)
    : QObject(parent),
      number(num),
      placeId(lieu),
      address(ip),
      isConnected(estConnecte)
{
}
