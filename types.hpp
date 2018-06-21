#pragma once

#include <exception>

enum class Suit 
{
	Clubs,
	Diamonds, 
	Hearts,
	Spades
};

enum class Face
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

enum class HandValue
{
	StraightFlush,
	FourOfAKind,
	FullHouse,
	Flush,
	Straight,
	ThreeOfAKind,
	TwoPair,
	OnePair,
	HighCard,
	None
};

Face FaceValueFromChar(char c);
Suit SuitFromChar(char c);

struct Card
{
	Card(Suit _suit, Face _face) : suit(_suit), faceValue(_face) {}
	Card(char _suit, char _face) : suit(SuitFromChar(_suit)), faceValue(FaceValueFromChar(_face)) {}

	Suit suit;
	Face faceValue;
};