# include <stdio.h>
# include <time.h>

int *input_array(int *len){
  printf("Input array:\n");
  scanf("%d", len);
  int *data = (*int) malloc(*len *sizeof(int));
  if (!data){
    printf("Input Error");
    return NULL;
  }
  return data;
}

int *array_remove_dups(int *data, int *len){
  for (int i = 0; i < *len-1; ++i){
    for (int j = i + 1; j < *len; ++j){
      if (data[i] == data[j]){
        for (int k = j; k < *len-1; ++k){
          data[k] = data[k+1];
        }
        len --;
        j --;
      }
    }
  }
  return data;
}

int print_array(int *data, int *len){
  for(int i = 0; i < *len; ++i){
    printf("data[%d] = ", i);
    scanf("%d", &data[i]);
  }
}

int main(){
  int len = 0;
  int i = input_array(*len);
  printf(i);
  /*
  int o = input_array(i, *len)
  */
  return 0;
}

