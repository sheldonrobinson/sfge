template <typename VectorStorageT>
std::shared_ptr<sf::Shape> shapeFromCircle(const Circle<VectorStorageT> &circle, const sf::Color &c)
{
    std::shared_ptr<sf::CircleShape> sf_circle(new sf::CircleShape(circle.mRadius));
    sf_circle->setPosition(circle.mPos);
    sf_circle->setPointCount(40);
    sf_circle->setFillColor(c);
	return sf_circle;
}
