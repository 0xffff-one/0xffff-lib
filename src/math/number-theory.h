#ifndef _NUMBER_THEORY_
#define _NUMBER_THEORY_

int gcd(int a, int b) {
  if (b == 0) return a;

  return gcd(b, a % b);
}

int lcm(int a, int b) {
	return a * b / gcd(a, b);
} 

#endif /* ifndef _NUMBER_THEORY_H_ */
