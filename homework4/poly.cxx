#include "poly.h"
using namespace std;

namespace main_savitch_5
{
//polynode
//double coef_field;		
//unsigned int exponent_field;
//polynode *link_fore;
//polynode *link_back;
	
//polynomial	
// polynode* head_ptr;		// Head pointer for list of nodes
//polynode* tail_ptr;		// Tail pointer for list of nodes
//mutable polynode* recent_ptr;		// Pointer to most recently used node
//unsigned int current_degree;		// Current degree of the polynomial

	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if(fabs(c) < EPSILON && exponent == 0){
			head_ptr = new polynode();
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else if(fabs(c) > EPSILON && exponent == 0){
			head_ptr = new polynode(c,0);
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else if(fabs(c) < EPSILON && exponent > 0){
			head_ptr = new polynode();
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else{
			head_ptr = new polynode();
			tail_ptr = new polynode(c, exponent, NULL, head_ptr);
			head_ptr->set_fore(tail_ptr);
			head_ptr->fore()->set_back(head_ptr);
			current_degree = exponent;
		}
		recent_ptr = head_ptr;
    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
 
		//check for self-assignment
		if(this == &source)
			return *this;

		this->clear(); //get rid of any pre-existing nodes
		
		if(source.head_ptr == nullptr){
			head_ptr = nullptr;
			return *this;
		}
		unsigned int exp = 0;		
		do{
			assign_coef(source.coefficient(exp), exp);
			exp = source.next_term(exp);
		} while(exp > 0);
		
		current_degree = source.degree();
		return *this;
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode();  //initialize new polynomial 
		tail_ptr = head_ptr;
		unsigned int exp = 0;
		do{	
			assign_coef(source.coefficient(exp), exp);		
			exp = source.next_term(exp);
		}while(exp > 0);
    }

    polynomial::~polynomial()
    {
		clear();
		delete head_ptr;
		head_ptr = NULL;
    }

    void polynomial::clear()
    {
		polynode* temp;
		while(head_ptr->fore() != nullptr){
			temp = head_ptr->fore();
			delete head_ptr;
			head_ptr = temp;
		}
		head_ptr->set_exponent(0);		
		head_ptr->set_coef(0);
		current_degree = 0;
		head_ptr->set_fore(NULL);
		head_ptr->set_back(NULL);
		recent_ptr = head_ptr;
		temp = NULL;

    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		if(recent_ptr->exponent() != exponent) //the requested exponent not found
			return 0.0;
		else
			return recent_ptr->coef();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);
		if(fabs(amount) < EPSILON) //adding 0 so do nothing 
			return;
		if(recent_ptr->exponent() == exponent)
			assign_coef((recent_ptr->coef() + amount), exponent);
		else
			assign_coef(amount, exponent);
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		if(exponent == 0){
			head_ptr->set_coef(coefficient);
			return;
		}	
		else if(exponent == current_degree){
			if(fabs(coefficient) < EPSILON){  //if coef 0 have to delete the node
				recent_ptr = recent_ptr->back();
				recent_ptr->set_fore(NULL);
				delete tail_ptr;
				tail_ptr = recent_ptr;
				current_degree = tail_ptr->exponent();
				return;
			}
			tail_ptr->set_coef(coefficient);
			return;
		}
		else if(exponent > current_degree && fabs(coefficient) > EPSILON){  //create new tail
			polynode* node = new polynode(coefficient, exponent, NULL, recent_ptr);
			recent_ptr->set_fore(node);
			recent_ptr = node;
			tail_ptr = recent_ptr;
			current_degree = exponent;
		}
		else if(recent_ptr->exponent() < exponent && fabs(coefficient) > EPSILON){ //new node somewhere in polynomial
			polynode* node = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
			recent_ptr->fore()->set_back(node);
			recent_ptr->set_fore(node);
			recent_ptr = node;
		}
		else if(fabs(coefficient) < EPSILON){
			if(recent_ptr->exponent() == exponent){  //deleting node somewhere in middle
				polynode* forward = recent_ptr->fore();
				polynode* backward = recent_ptr->back();
				forward->set_back(backward);
				backward->set_fore(forward);
				delete recent_ptr;
				recent_ptr = backward;
			}
		}
		else
			recent_ptr->set_coef(coefficient);
    }

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
			if(exponent >= current_degree)
				return 0;
			set_recent(exponent);
			
			if(recent_ptr->fore() == NULL)
				return 0;
			else
				return (recent_ptr->fore()->exponent());
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if(exponent == 0)
			return UINT_MAX;
		set_recent(exponent-1);
		if(recent_ptr == NULL)
			return UINT_MAX;
		if(fabs(recent_ptr->coef()) < EPSILON)
			return UINT_MAX;
		else
			return (recent_ptr->exponent());
		
		
    }
    
    void polynomial::set_recent(unsigned int exponent) const
    {
		if(exponent == 0){
			recent_ptr = head_ptr;
			return;
		}
		else if(exponent >= current_degree){
			recent_ptr = tail_ptr;
			return;
		}
		else if(recent_ptr->exponent() == exponent)
			return;
		else{
			if(recent_ptr->exponent() < exponent){
				while(recent_ptr->exponent() <= exponent && recent_ptr->fore() != NULL){
					if(recent_ptr->exponent() == exponent)
						return;
					recent_ptr = recent_ptr->fore();
				}
			}
			else if(recent_ptr->exponent() > exponent){
				while(recent_ptr->exponent() >= exponent && recent_ptr->back() != NULL){
					if(recent_ptr->exponent() == exponent)
						return;				
					recent_ptr = recent_ptr->back();
				}
			}
			if(recent_ptr->exponent() > exponent)
					recent_ptr = recent_ptr->back(); //exponent not in list so go back one for closest 			
		}
	}	
    
    double polynomial::eval(double x) const
    {
		double total = 0, term = 0;
		unsigned int exp = 0;
		do{
			term = coefficient(exp)* pow(x, (double) exp);
			total += term;
			exp = next_term(exp);
		}while(exp > 0);
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		unsigned int exp = next_term(0);
		
		while(exp > 0){
			p_prime.assign_coef(coefficient(exp)*exp, exp-1);
			exp = next_term(exp);
		}
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		unsigned int exp1 = 0, exp2 = 0;
		do{
			p.add_to_coef(p1.coefficient(exp1), exp1);
			exp1 = p1.next_term(exp1);
		}while(exp1 > 0);
		
		do{
			p.add_to_coef(p2.coefficient(exp2), exp2);		
			exp2 = p2.next_term(exp2);	
		}while(exp2 > 0);			
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p, neg(-1,0);
		p = p1 + (neg*p2);
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		unsigned int exp1 = 0, exp2 = 0;
		do{
			do{
				p.add_to_coef(p1.coefficient(exp1)*p2.coefficient(exp2), exp1+exp2);
				exp2 = p2.next_term(exp2);
			}while(exp2 > 0);
			exp1 = p1.next_term(exp1);
		}while(exp1 > 0);
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0) out << " + ";
		} while(expo != 0);

		return out;
    }
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
		iterations = 0;
		success = false;
		double y, dy;

		while(iterations < maximum_iterations && success == false){
			y = eval(guess);
			if(fabs(y) < epsilon){  //found root, y = 0
				answer = guess; 
				success = true;
			}
			
			dy = derivative().eval(guess);
			if(fabs(dy) < epsilon)  //if dy = 0 no root
				break;
			guess -= y / dy; //newtons method
			iterations++;
		}
	}
}
