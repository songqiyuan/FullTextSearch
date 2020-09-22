#include "Hit.h"
#include<iostream>
CHit::CHit():
	_match(NOT_MATCH),_text("")
{
}
CHit::~CHit()
{

}
void CHit::setText(const string str)
{
	_text += str;
}
string CHit::getText()
{
	return _text;
}
void CHit::setMatch()
{
	_match |= MATCH;
}
void CHit::setPrefix()
{
	_match |= PREFIX;
}
void CHit::setNotMatch()
{
	_match = NOT_MATCH;
}
bool CHit::isNotMatch()
{
	return (_match == NOT_MATCH);
}
bool CHit::isMatch()
{
	return (_match&MATCH);
}
bool CHit::isPrefix()
{
	return (_match&PREFIX);
}
int CHit::getMatch()
{
	return _match;
}
void CHit::setCurrNode(const signleNode& hitNode)
{
	_HitNode = hitNode;
}
signleNode CHit::getCurrNode()
{
	return _HitNode;
}
void CHit::displayText()
{
	std::cout << _text << std::endl;
}
