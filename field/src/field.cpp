#include "field.h"


namespace gm
{
    void Field::hold()
    {
        if (holding)
            return;
        if (hold_piece.empty())
        {
            hold_piece = one_piece.get_tetromino();
            one_piece = pick();
            one_piece.set_playfield(std::make_shared<Matrix>(field));
        }
        else
        {
            auto tmp = hold_piece;
            hold_piece = one_piece.get_tetromino();
            one_piece = Piece(tmp, 4, 20, 0);
            one_piece.set_playfield(std::make_shared<Matrix>(field));
        }
        holding = true;
    }

    void Field::levelup()
    {
        level = lines / 10 + 1;
        duration = std::chrono::milliseconds((int)(pow(0.8 - (level - 1) * 0.007, level - 1) * 1000));
    }

    void Field::reset()
    {
        init();
        reseting = true;
    }

    void Field::help()
    {
        helping = !helping;
        reseting = !helping;
    }
    void Field::process()
    {
        if (ending)
        {
            return;
        }
        render();
        if (ut::timer(duration))
        {
            if (one_piece.down())
                return;
            // 如果无法继续下落，就锁定
            if (locking)
            {
                lock();
                // 消除行
                clear();
                one_piece = pick();
                levelup();
                locking = false;
                holding = false;
                reseting = false;
            }
            else
            {
                locking = true;
            }
        }
    }
    void Field::render()
    {
        frame = field;
        // //shadow mino
        merge(frame, one_piece);
        Piece ghost = one_piece;
        ghost.set_ghost();
        // while(one_piece.test(x,--y));
        // y++;

        while (ghost.down())
            ;
        merge(frame, ghost);
    }
    Piece Field::pick()
    {
        assert(next.size() > 0);
        Piece p(next.front(), 4, 20, 0);
        // Piece p(j,4,20,0);
        p.set_playfield(std::make_shared<Matrix>(field));
        if (!p.test(4, 20))
        {
            ending = true;
        }
        next.pop();
        preview();
        return std::move(p);
    }
    void Field::lock()
    {
        gm::merge(field, one_piece);

    }
    void Field::clear()
    {
        int count = 0;
        for (auto it = field.begin(); it != field.end(); ++it)
        {
            bool full = true;
            for (auto cell : *it)
            {
                if (cell == 0)
                {
                    full = false;
                    break;
                }
            }
            if (full)
            {
                it = field.erase(it);
                field.push_back(std::vector<int>(it->size(), 0));
                it--;
                count++;
            }
        }
        switch (count)
        {
        case 1:
            score += 100 * level;
            break;
        case 2:
            score += 300 * level;
            break;
        case 3:
            score += 500 * level;
            break;
        case 4:
            score += 800 * level;
            break;
        default:
            break;
        }
        lines += count;
    }
    void Field::init()
    {
        running = true;
        locking = false;
        holding = false;
        ending = false;
        reseting = false;
        helping = false;
        score = 0;
        lines = 0;
        levelup();
        // field[y][x],x=0~9,y=0~21, 10*20
        field = Matrix(22, std::vector<int>(10, 0));
        // load();
        preview();
        one_piece = pick();
        frame = field;
    }
    void Field::quit()
    {
        running = false;
    }
    void Field::rotate(int i)
    {
        one_piece.rotate(i);
    }
    void Field::left()
    {
        one_piece.left();
    }
    void Field::right()
    {
        one_piece.right();
    }
    void Field::down()
    {
        if (one_piece.down())
            score++;
    }
    void Field::drop()
    {
        while (one_piece.down())
            score += 2;
        locking = true;
    }
    void Field::preview()
    {
        static std::vector<Tetromino> bag{i, j, l, o, s, t, z};
        int index;
        while (next.size() < 5)
        {
            index = rand() % bag.size();
            next.push(bag[index]);
            bag.erase(bag.begin() + index);
            if (bag.size() == 0)
                bag = {i, j, l, o, s, t, z};
        }
    }
}