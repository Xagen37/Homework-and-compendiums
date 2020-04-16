package md2html.markup;

public class Text implements MarkdownUnit {
    private String m_text;

    public Text() {
        m_text = "";
    }

    public Text(String text) {
        m_text = text;
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        source.append(m_text);
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append(m_text);
    }
}
