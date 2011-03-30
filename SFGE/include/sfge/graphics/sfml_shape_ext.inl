template <typename VectorStorageT>
sf::Shape shapeFromCircle(const Circle<VectorStorageT> &circle, const sf::Color &c)
{
	return sf::Shape::Circle(circle.mPos, circle.mRadius, c);
}
