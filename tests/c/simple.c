int main() {
  volatile long arr[5] = {1, 2, 3, 4, 5};
  volatile long sum = 0;

  for (int i = 0; i < 5; i++) {
    sum += arr[i];
  }

  long result = 0;
  if (sum == 15) {
    result = 0xCAFEBABE; 
  } else {
    result = 0xDEADBEEF; 
  }

  return result;
}