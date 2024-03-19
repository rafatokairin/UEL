package uel.br.produtos;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.CollectionUtils;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;

import java.util.ArrayList;
import java.util.List;

@Controller
public class ProdutoController {
    private static final String SESSION_CARRINHO = "sessionCarrinho";
    @Autowired
    ProdutoRepository produtoRepository;
    @GetMapping("/novo-produto")
    public String mostrarFormNovoProduto(Produto produto){
        return "novo-produto";
    }
    @GetMapping(value={"/index", "/"})
    public String mostrarListaProduto(Model model) {
        model.addAttribute("produtos", produtoRepository.findAll());
        return "index";
    }
    @PostMapping("/adicionar-produto")
    public String adicionarProduto(@Valid Produto produto, BindingResult result) {
        if (result.hasErrors()) {
            return "/novo-produto";
        }
        produtoRepository.save(produto);
        return "redirect:/index";
    }
    @GetMapping("/editar/{id}")
    public String mostrarFormAtualizar(@PathVariable("id") int id, Model model) {
        Produto produto = produtoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do produto é inválido:" + id));
        model.addAttribute("produto", produto);
        return "atualizar-produto";
    }
    @PostMapping("/atualizar/{id}")
    public String atualizarProduto(@PathVariable("id") int id, @Valid Produto produto,BindingResult result, Model model) {
        if (result.hasErrors()) {
            produto.setId(id);
            return "atualizar-produto";
        }
        produtoRepository.save(produto);
        return "redirect:/index";
    }
    @GetMapping("/remover/{id}")
    public String removerProduto(@PathVariable("id") int id, HttpServletRequest request) {
        Produto produto = produtoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do produto é inválido:" + id));
        produtoRepository.delete(produto);
        List<Produto> sessionCarrinho = (List<Produto>) request.getSession().getAttribute(SESSION_CARRINHO);
        sessionCarrinho.remove(produto);
        request.getSession().setAttribute(SESSION_CARRINHO, sessionCarrinho);
        return "redirect:/index";
    }
    @GetMapping("/adicionarCarrinho/{id}")
    public String adicionarCarrinhoProduto(@PathVariable("id") int id, HttpServletRequest request) {
        Produto produto = produtoRepository.findById(id).orElseThrow(() -> new IllegalArgumentException("O id do produto é inválido: " + id));
        List<Produto> carrinho = (List<Produto>) request.getSession().getAttribute(SESSION_CARRINHO);
        if (CollectionUtils.isEmpty(carrinho)) {
            carrinho = new ArrayList<>();
        }
        boolean produtoJaNoCarrinho = false;
        for (Produto p : carrinho) {
            if (p.getId() == produto.getId() && p.getQuantidade() < produto.getQuantidade()) {
                p.setQuantidade(p.getQuantidade() + 1);
                produtoJaNoCarrinho = true;
                break;
            }
        }
        if (!produtoJaNoCarrinho && produto.getQuantidade() > 0) {
            // Calcula quantidade total de produto no carrinho
            int quantidadeTotalNoCarrinho = carrinho.stream().filter(p -> p.getId() == produto.getId()).mapToInt(Produto::getQuantidade).sum();
            // Verifica se quantidade total carrinho + quantidade a ser adicionada nao excede quantidade disponivel
            int quantidadeDisponivel = produto.getQuantidade() - quantidadeTotalNoCarrinho;
            if (quantidadeDisponivel > 0) {
                Produto produtoCarrinho = new Produto();
                produtoCarrinho.setId(produto.getId());
                produtoCarrinho.setNome(produto.getNome());
                produtoCarrinho.setPreco(produto.getPreco());
                produtoCarrinho.setQuantidade(1); // Quantidade inicial carrinho = 1
                carrinho.add(produtoCarrinho);
            }
        }
        request.getSession().setAttribute(SESSION_CARRINHO, carrinho);
        return "redirect:/carrinho";
    }
    @GetMapping("/carrinho")
    public String mostrarCarrinho(Model model, HttpServletRequest request){
        List<Produto> carrinho = (List<Produto>) request.getSession().getAttribute(SESSION_CARRINHO);model.addAttribute("sessionCarrinho", !CollectionUtils.isEmpty(carrinho) ? carrinho : new ArrayList<>());
        return "carrinho";
    }
    @GetMapping("/carrinho/remover/{id}")
    public String removerCarrinho(@PathVariable("id") int id, HttpServletRequest request) {
        List<Produto> sessionCarrinho = (List<Produto>) request.getSession().getAttribute(SESSION_CARRINHO);
        Produto produto = null;
        for (Produto p : sessionCarrinho) {
            if (p.getId() == id) {
                produto = p;
                break;
            }
        }
        if (produto != null && produto.getQuantidade() > 0) {
            produto.setQuantidade(produto.getQuantidade() - 1);
        }
        // Remover o produto do carrinho apenas se a quantidade for 0
        if (produto != null && produto.getQuantidade() == 0) {
            sessionCarrinho.remove(produto);
        }
        request.getSession().setAttribute(SESSION_CARRINHO, sessionCarrinho);
        return "redirect:/carrinho";
    }
}