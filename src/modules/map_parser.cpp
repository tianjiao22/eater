#include "modules/map_parser.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>

using namespace std;

    struct _server_data {
            std::vector<int> _positions;
	    std::vector<int> _scores;
            int _id;
	    int _size;
	    char *_map;
	};
server_data::server_data() {

}

server_data::server_data(char *map,
		int size, int id, std::vector<int> &poses, std::vector<int> &scores) {
	// TODO
        this->_map = new char [size * size ];
        memcpy(this->_map ,map ,size * size);
        this-> _size = size;
        this ->_id = id;
        this->_positions = poses;
        this->_scores = scores;
}
server_data::~server_data()
{
	// TODO
    delete _map;

}

class server_data server_data::clone() {
	// TODO
    struct   _server_data d1;
        d1._id = this->_id;
        d1._size = this->_size;
        d1._positions = this->_positions;
        d1._scores = this->_scores;
        d1._map = this->_map;
	return server_data(d1._map, d1._size,d1._id,d1._positions,d1._scores) ;
}

int server_data::get_map_size() {
	// TODO
	return this->_size ;
}

char server_data::get(int row, int col) {
	// TODO
    if(row > (this->_size -1)
        || col > (this->_size -1 )
        || row * col >= pow(this->_size,2)) {
        return 0;//越界返回0.
    }
    if ( !this->_map  ) {
        return 0;
    }

    //计算Map 方阵，每个的位置
    int index = (row * this->_size) + (col +1);
	return this->_map[index-1];

}

int server_data::get_score_by_pos(int pos) {
	// TODO
    int score = 0;
    if (_scores .size() < _positions.size() ) {
        return 0;
    }

    for ( int n = 0; n < _positions.size(); n++) {
        if (_positions[n] == pos) {
            score = _scores[n];
        }

    }
	return score;
}

void server_data::get_my_pos(int &row, int &col) {
	// TODO
    if (_positions [_id] % this->_size != 0) {
        row = _positions [_id] / this->_size;
        col = _positions [_id] - (row * this->_size) - 1;
    }
    else {
        col = this->_size -1;
        row = _positions [_id] / this->_size -1;
    }
}

int server_data::get_my_score() {
	// TODO
    if ( _scores.size() == _positions.size() ) {
        return (int)this ->_scores[_id];
    }
    else {
        return 0;
    }
}

int server_data::move(enum move_operating move_op) {
	// TODO
	return 0;
}

int server_data::fire() {
	// TODO
	return 0;
}
