#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <climits>

int main()
{
    const int SIZE = 10000;
    std::vector<int> nums(SIZE);

    // 生成随机测试数据（可替换为实际输入）
    for (int i = 0; i < SIZE; ++i)
    {
        nums[i] = rand(); // 生成0~RAND_MAX的随机数
    }

    int pipefd[2]; // 创建管道
    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // 创建子进程
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {                     // 子进程处理前5000个数
        close(pipefd[0]); // 关闭读取端
        int max_part = INT_MIN;
        for (int i = 0; i < SIZE / 2; ++i)
        {
            if (nums[i] > max_part)
                max_part = nums[i];
        }
        // 将结果写入管道
        if (write(pipefd[1], &max_part, sizeof(int)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        exit(EXIT_SUCCESS);
    }
    else
    {                     // 父进程处理后5000个数
        close(pipefd[1]); // 关闭写入端
        int max_parent = INT_MIN;
        for (int i = SIZE / 2; i < SIZE; ++i)
        {
            if (nums[i] > max_parent)
                max_parent = nums[i];
        }
        // 等待子进程结束
        wait(nullptr);
        int max_child;
        if (read(pipefd[0], &max_child, sizeof(int)) == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        // 比较结果
        int overall_max = std::max(max_parent, max_child);
        std::cout << "最大值: " << overall_max << std::endl;
    }
    return 0;
}