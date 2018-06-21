#pragma once

#include "types.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>


Face FaceValueFromChar(char c)
{

	if(c >= '2' && c <= '9')
		return static_cast<Face>(c - '0' - 1);

	else if(c == 'A')
		return Face::Ace;
	else if(c == 'T')
		return  Face::Ten;
	else if(c == 'J')
		return  Face::Jack;
	else if(c == 'Q')
		return  Face::Queen;
	else if(c == 'K') 
		return  Face::King;
	else
		throw std::runtime_error("invalid face value");
}

Suit SuitFromChar(char c)
{
	switch(c)
	{
		case 'C':
			return Suit::Clubs;
		case 'D':
			return Suit::Diamonds;
		case 'H':
			return Suit::Hearts;
		case 'S':
			return Suit::Spades;
		default:
			throw std::runtime_error("invalid suit value");
	}

}

std::ostream& operator<<(std::ostream& os, const Suit& suit)
{
	switch(suit)
	{
		case Suit::Spades:
			os << 'S';
			break;
		case Suit::Hearts:
			os << 'H';
			break;
		case Suit::Diamonds:
			os << 'D';
			break;
		case Suit::Clubs:
			os << 'C';
			break;
	};

	return os;
}

std::ostream& operator<<(std::ostream& os, const Face& face)
{
	switch(face)
	{
		case Face::Ace:
			os << 'A';
			break;
		case Face::Two:
			os << '2';
			break;
		case Face::Three:
			os << '3';
			break;
		case Face::Four:
			os << '4';
			break;
		case Face::Five:
			os << '5';
			break;
		case Face::Six:
			os << '6';
			break;
		case Face::Seven:
			os << '7';
			break;
		case Face::Eight:
			os << '8';
			break;
		case Face::Nine:
			os << '9';
			break;
		case Face::Ten:
			os << 'T';
			break;
		case Face::Jack:
			os << 'J';
			break;
		case Face::Queen:
			os << 'Q';
			break;
		case Face::King:
			os << 'K';
			break;
	};

	return os;
}

std::ostream& operator<<(std::ostream& os, const HandValue& handValue)
{
	switch(handValue)
	{
		case HandValue::StraightFlush:
			os << "straight-flush";
			break;
		case HandValue::FourOfAKind:
			os << "four-of-a-kind";
			break;
		case HandValue::FullHouse:
			os << "full-house";
			break;
		case HandValue::Flush:
			os << "flush";
			break;
		case HandValue::Straight:
			os << "straight";
			break;
		case HandValue::ThreeOfAKind:
			os << "three-of-a-kind";
			break;
		case HandValue::TwoPair:
			os << "two-pairs";
			break;
		case HandValue::OnePair:
			os << "one-pair";
			break;
		case HandValue::HighCard:
			os << "highest-card";
			break;
	};

	return os;
}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
	os << card.faceValue << card.suit;
	return os;
}

bool FaceAdjacency(Face f1, Face f2)
{
	if(f1 == Face::Ace || f2 == Face::Ace)	
		return f2 == Face::King || f2 == Face::Two || f1 == Face::King || f1 == Face::Two;

	if(f1 == Face::King || f2 == Face::King)
		return f1 == Face::Ace || f1 == Face::Queen || f2 == Face::Ace || f2 == Face::Queen;
	
	int faceValueDistance = abs(static_cast<int>(f1) - static_cast<int>(f2));
	return  faceValueDistance == 1;	
}