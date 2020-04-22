#pragma once

#include <svgdom/visitor.hpp>

#include "Renderer.hxx"

namespace svgren{

struct FilterResult{
	std::vector<std::uint8_t> data;
	Surface surface;
};

class FilterApplier : public svgdom::const_visitor{
	Renderer& r;

	decltype(svgdom::FilterElement::primitive_units) primitiveUnits;
	
	CanvasRegion filterRegion;
	
	std::map<std::string, FilterResult> results;
	
	FilterResult* lastResult = nullptr;
	
	Surface getSource(const std::string& in);
	void setResult(const std::string& name, FilterResult&& result);
	
	Surface getSourceGraphic();
	
public:
	
	Surface getLastResult();
	
	FilterApplier(Renderer& r) : r(r) {}
	
	void visit(const svgdom::FilterElement& e)override;
	
	void visit(const svgdom::FeGaussianBlurElement& e)override;
	void visit(const svgdom::FeColorMatrixElement& e) override;
	void visit(const svgdom::FeBlendElement& e) override;
	void visit(const svgdom::FeCompositeElement& e) override;

};

}
