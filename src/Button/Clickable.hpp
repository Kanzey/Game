#ifndef CLICKABLE_HPP
#define	CLICKABLE_HPP

class Clickable {    
public:
    virtual void onClick() {};
    virtual void onClick(const sf::RenderTarget & renderTargert) { };
};

#endif	/* CLICKABLE_HPP */

