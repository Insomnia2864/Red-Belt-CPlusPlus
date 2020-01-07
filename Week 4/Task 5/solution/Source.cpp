#include <list>
#include "test_runner.h"

class Editor 
{
public:
    Editor();
    void Left();
    void Right();
    void Insert(char token);
    void Cut(size_t tokens = 1);
    void Copy(size_t tokens = 1);
    void Paste();
    std::string GetText() const;
private:
    std::list<char> txt;
    std::list<char>::iterator ptr;
    std::list<char> ctrl_c;
};

Editor::Editor() :
    ptr(txt.begin())
{}

void Editor::Left()
{
    if (ptr != txt.begin())
    {
        ptr--;
    }
}

void Editor::Right()
{
    if (ptr != txt.end())
    {
        ++ptr;
    }
}

void Editor::Insert(char token)
{
    txt.insert(ptr, token);
}

void Editor::Cut(size_t tokens)
{
    ctrl_c.clear();
    auto it = ptr;
    while (tokens-- != 0 && it != txt.end())
    {
        it++;
    }
    ctrl_c.splice(ctrl_c.begin(), txt, ptr, it);
    ptr = it;
}

void Editor::Copy(size_t tokens)
{
    auto iter = ptr;
    ctrl_c.clear();

    while (tokens != 0 && iter != txt.end())
    {
        tokens--;
        ctrl_c.push_back(*(iter++));
    }
}

void Editor::Paste()
{
    txt.insert(ptr, ctrl_c.begin(), ctrl_c.end());
}

std::string Editor::GetText() const
{
    return std::string(txt.begin(), txt.end());
}

void TypeText(Editor& editor, const std::string& text) 
{
    for (char c : text) 
    {
        editor.Insert(c);
    }
}

void TestEditing() 
{
    {
        Editor editor;

        const std::size_t text_len = 12;
        const std::size_t first_part_len = 7;
        TypeText(editor, "hello, world");

        for (std::size_t i = 0; i < text_len; i++)
        {
            editor.Left();
        }

        editor.Cut(first_part_len);

        for (std::size_t i = 0; i < text_len - first_part_len; i++)
        {
            editor.Right();
        }

        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() 
{
    Editor editor;

    const std::string text = "esreveR";
    for (char c : text) 
    {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() 
{
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() 
{
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

int main() 
{
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}