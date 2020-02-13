#include <iostream>
#include <math.h>
using namespace std;

void merge(int arr[], int low, int high)
{
    int temp[high - low + 1], pos = 0, l = low, h = high;
    int mid = (low + high) / 2, low2 = mid + 1;

    while (pos <= h - l + 1)
    {
        if (low <= mid)
        {
            if (low2 <= high && arr[low] > arr[low2])
            {
                temp[pos] = arr[low2];
                low2++;
            }
            else
            {
                temp[pos] = arr[low];
                low++;
            }
        }
        else
        {
            temp[pos] = arr[low2];
            low2++;
        }
        pos++;
    }

    for (int i = l; i <= h; i++)
    {
        arr[i] = temp[i - l];
    }
}

void merge_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);

        merge(arr, low, high);
    }
}

void storage(int **tapes, int *song, int num_tapes, int n)
{
    for (int i = 0; i < n; i++)
        tapes[i % num_tapes][i / num_tapes] = song[i];
}

double cal_avg(int **tape, int t, int len)
{
    double avg = 0;
    for (int i = 0; i < t; i++)
    {
        double mrt = 0;
        int count = 0;
        for (int j = 0; j < len; j++)
        {
            mrt += tape[i][j];
            if (tape[i][j])
                count++;
        }
        for (int j = 0; j < count; j++)
            mrt += tape[i][j] * (count - j - 1);
        mrt = mrt / len;
        avg += mrt;
    }

    avg = avg / t;

    return avg;
}

int main()
{
    int n, *song, num_tape, **tapes, len_tape;
    float avg;

    cout << "Enter the number of songs" << endl;
    cin >> n;

    song = new int[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the length of size " << i + 1 << endl;
        cin >> song[i];
        while (song[i] < 0)
        {
            cout << "Length of song cannot be negative" << endl;
            cin >> song[i];
        }
    }

    merge_sort(song, 0, n - 1);
    cout << "Enter the number of tapes" << endl;
    cin >> num_tape;

    tapes = new int *[num_tape];
    len_tape = ceil((double)n / num_tape);

    for (int i = 0; i < num_tape; i++)
        tapes[i] = new int[len_tape];

    storage(tapes, song, num_tape, n);

    cout << "DISPLAY THE TAPE" << endl;

    for (int i = 0; i < num_tape; i++)
    {

        cout << "TAPE " << i + 1 << " ";
        for (int j = 0; j < len_tape; j++)
        {
            cout << tapes[i][j];
            cout << " ";
        }
        cout << endl;
    }

    avg = cal_avg(tapes, num_tape, len_tape);

    cout << "AVG is " << avg << endl;
    return 0;
}