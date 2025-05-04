import socket
import time
from bready.socket_utils import SocketManager
from bready.socket_utils import Bready_Protocol

class AutoVehicleControlClient(SocketManager.SocketClient):
    # ip : 연결할 서버의 IP
    # port : 연결할 서버의 Port
    # name : 연결할 서버를 구분하기 위한 용도 (ex: iotGateway, AutoVehicle, iotMakers .. 등등)
    def __init__(self, ip="127.0.0.1", port=10004):
        super().__init__(ip, port, "AutoVehicle Control")
        self.ser_socket_packet = Bready_Protocol.Packet()
        self.ultrasonic = 0
        self.battery = 0

    # 소켓 서버에 bready protocol 패킷 전송
    def sendData(self):
        try:
            if(not self.ser_socket_connect_status):
                return
            self.ser_socket_packet.setID(0x10)
            self.ser_socket_packet.setCMD(0xC1)
            self.ser_socket_packet.calcLRC()
            if(self.ser_socket_packet.getLength() > 1):
                self.ser_socket.send(bytes(self.ser_socket_packet.packetToList()))
                # print("[Server Manager] {0}:{1} 서버로 데이터를 송신하였습니다.".format(self.ip, self.port))
        except ConnectionResetError:
            self.close()
            print("[Server Manager] {0}:{1} 서버와의 연결이 끊겼습니다.".format(self.ip, self.port))
            pass
        except socket.error as e:
            self.close()
            print("[Server Manager] {0}:{1} 서버와의 연결이 끊겼습니다.".format(self.ip, self.port))
            pass
        finally:
            self.ser_socket_packet.clearPayload()

    # 소켓 서버로부터 bready protocol 패킷 수신
    def receiveData(self):
        receivceList = []
        parsing = False
        parseComplete = False

        while(True):
            try:
                data = self.ser_socket.recv(self.receiveBuffer)
                if data is not None:
                    if not (len(data) == 0):
                        i = 0
                        while i < len(data):
                            if data[i] == 0x02:
                                parsing = True
                                parseComplete = False
                                receivceList.clear()
                                receivceList.append(data[i])
                            elif data[i] == 0x03:
                                parsing = False
                                parseComplete = True
                                receivceList.append(data[i])
                            elif parsing:
                                receivceList.append(data[i])
                            i = i + 1

                        if parseComplete:
                            p = Bready_Protocol.Packet()
                            if (p.parsingList(receivceList)):
                                self.processProtocol(p)
                            parseComplete = False

                    else:
                        print("disconnect..from " + str(self.getServerIP()))
                        break

            except ConnectionResetError:
                pass
            except socket.error as e:
                pass
            finally:
                time.sleep(0.01)

    def processProtocol(self, p):
        if(p.getID() == 0x10):
            if(p.getCMD() == 0xB0):
                for payload in p.getPayload():
                    if(payload.getID() == 0x80):
                        self.battery = int(payload.getData())
                    if(payload.getID() == 0x81):
                        self.ultrasonic = float(payload.getData())

    # bready protocol 패킷에 데이터 추가
    def controlDirection(self, data):
        self.ser_socket_packet.addPayload(0x80, data)

    def controlMotor(self, data):
        self.ser_socket_packet.addPayload(0x81, data)

    def controlHeadlight(self, data):
        self.ser_socket_packet.addPayload(0x84, data)

    def controlHorn(self, data):
        self.ser_socket_packet.addPayload(0x85, data)

    def readBattery(self):
        return self.battery

    def readUltrasonic(self):
        return self.ultrasonic
