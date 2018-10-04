<?php

class Connector {

    private $socket;
    private $port;
    private $host;

    public function __construct($host, $port) {
        $this->host = $host;
        $this->port = $port;
        $this->socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
        if (!$this->socket) {
            exit('socket creation error.');
        }
        $result = socket_connect($this->socket, $this->host, $this->port);
        if (!$result) {
            exit('socket connection error.' . $this->host);
        }
    }

    public function send($data) {
        $head = pack("L", strlen($data));
        $result = socket_write($this->socket, $head . $data);
        if (!$result) {
            exit('message sending error');
        }
        return $result;
    }

    public function recv() {
        $head = socket_recv($this->socket, $buf, 4, MSG_OOB / MSG_PEEK);
        if (!$head) {
            exit('message receiving error');
        } else {
            socket_recv($this->socket, $buf, 67108864, MSG_OOB / MSG_PEEK);
            return $buf;
        }
    }

    public function build($db_name, $rdf_file_path) {
        $data = "import " . $db_name . " " . $rdf_file_path . "\0";
        self::send($data);
        $result = self::recv();
        return $result;
    }

    public function load($db_name) {
        $data = "load " . $db_name . "\0";
        self::send($data);
        $result = self::recv();
        return $result;
    }

    public function unload($db_name) {
        $data = "unload " . $db_name;
        self::send($data);
        $result = self::recv();
        return $result;
    }

    public function query($sparql) {
        $data = "query " . $sparql . "\0";
        self::send($data);
        $result = self::recv();
        return $result;
    }

    public function __desctruct() {
        socket_close($this->socket);
    }

}

?>